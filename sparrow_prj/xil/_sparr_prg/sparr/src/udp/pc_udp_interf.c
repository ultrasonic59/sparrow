///#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <signal.h>
#include <sys/socket.h>
#include <resolv.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <getopt.h>
#include <pthread.h>
#include <fcntl.h>
#include <time.h>
#include <syslog.h>

#include <dirent.h>

#include "../../../common_inc/sparrow_types.h"
///#include "sparrow_types.h"
#include "../inc/sparrow_cnf.h"
#include "../inc/my_types.h"
#include "../inc/sparrow_udp_cmds.h"
#include "../inc/sparrow_fpga.h"
#include "../../../common_inc/sparrow_ioctl.h"

extern int puts_xil_dat(xil_dat_req_t *xil_req);

extern int mod_fd;

extern void set_rec_param(u8* ibuf);

extern void addfcs16( register unsigned char *cp, register int len );
extern int checkfcs16(unsigned char *cp, register int len );

extern u8 buffOscs[NUM_OSC][MAX_OSC_LEN];

extern u8 *zbuf1;

extern xil_dat_req_t g_xil_dat;
extern dac_spi_req_t g_dac_dat;


u16	pc_get_req_dat(u8 num_req,u8 *buf);
int pc_set_rec_dat(u8 cmd,void *in_buf);
volatile u8 cur_rej=0;
volatile u8 prev_rej=0;
///u16 onCN=0;
unsigned char volatile dev_state=0;
///=======================================
udp_stat_t g_udp_stat;
///adc_spi_req_t g_adc_spi_dat;
///==================================
u16 udp_set_frame(u8 *data, int len)
{
addfcs16(data,len);				///
memcpy(g_udp_stat.snd_buff,data,len +2);
return len +2;
}

u16	udp_send_ack_to(u8 ipar)
{
u8 p_tmp[8];
p_tmp[0]  = CMD_ACK;
p_tmp[1] = ipar;
return udp_set_frame(p_tmp, 2);
}


int	udp_set_ans(u8 type_send,u8 type_dat)
{
int res=0;
u16 len_dat;
int num_send=0;
u8 *p_tmp1;
u8 *p_tmp	 = g_udp_stat.t_snd_buff1;
if(type_send == SEND_ACK)
	{
	res=udp_send_ack_to(type_dat);
	}
else if(type_send == SEND_REQ_DAT)
	{
	*p_tmp++  = CMD_PUT_REQ_DAT;
	num_send++;
	*p_tmp++  = type_dat;
	num_send++;
	p_tmp1 = p_tmp+2;  
	len_dat = pc_get_req_dat(type_dat,p_tmp1);
	*p_tmp++  = len_dat&0xff;
	num_send++;
	*p_tmp++  = (len_dat>>8)&0xff;
	num_send++;
	if(len_dat > MAX_FRAME_LEN)
		len_dat = MAX_FRAME_LEN;
	num_send += len_dat;
	res=udp_set_frame(g_udp_stat.t_snd_buff1, num_send);
	}
else if(type_send == SEND_DAT)
	{
	num_send = g_udp_stat.snd_buff2_len;
	memcpy(p_tmp,g_udp_stat.t_snd_buff2,num_send);
	res=udp_set_frame(g_udp_stat.t_snd_buff1, num_send);
	}
else if(type_send == SEND_REQ)
	{
	num_send = g_udp_stat.snd_buff2_len;
	memcpy(p_tmp,g_udp_stat.t_snd_buff2,num_send);
	res=udp_set_frame(g_udp_stat.t_snd_buff1, num_send);
	}
return res;
}

u16 udp_parse_framein(u8 *in_buf,u16 len)
{
u16 rez =0;
u8 btmp;
///u16 htmp;
switch(*in_buf)
	{
	case CMD_ACK:			////???
		btmp = *(in_buf+1);
		rez =0;
		break;	
	case CMD_PUT_DAT:
		btmp = *(in_buf+1);
		pc_set_rec_dat(btmp,(void *)((u32)in_buf+2));
		rez =udp_set_ans(SEND_ACK,btmp);
		break;
	case CMD_PUT_REQ_DAT:
		btmp = *(in_buf+1);
		pc_set_rec_dat(btmp,(void *)((u32)in_buf+2));
		rez =0;
		break;
	case CMD_REQ_DAT:
		btmp = *(in_buf+1);
		g_udp_stat.offs_snd_buf = *(in_buf+2);
		g_udp_stat.offs_snd_buf |= (*(in_buf+3))<<8;
		rez =udp_set_ans(SEND_REQ_DAT,btmp);
		break;
	}
return rez;
}

int udp_check_framein(u8 *i_buff,u16 i_len)
{
int res = 1;
if(i_len < 3 )
	{
////	g_udp_stat.err_len++;
	res = -1;
	}
if( !checkfcs16(i_buff, i_len - 2 ) )
	{
///		g_udp_stat.err_fcs++;
		res = -2;
	}
return res;
}
///+++++++++++++++++++++++++++++++++++++++++++++++++++++
u16 obr_udp_cmd(u8 *i_buff,u16 i_len,u8 *o_buff)
{
int res;
u16 rez=0;
u16 ii;
if((res= udp_check_framein(i_buff,i_len))>0 )	//
	{
///==================================
	rez=udp_parse_framein(i_buff,i_len);
	}
else
	{
	rez=0;
    fprintf(stderr,"\n udp error framein[%d]\n",res);
    for(ii=0;ii<i_len;ii++)
    {
     fprintf(stderr,"[%x:%x]",ii,i_buff[ii]);

    }
    fprintf(stderr,"\n ");

	}
return rez;	
}
///+++++++++++++++++++++++++++++++++++++++++++++++++++++
void udp_pc_init(void)
{
g_udp_stat.in_buf = (u8*) malloc(MAX_FRAME_LEN);
if( g_udp_stat.in_buf == NULL ) 
///	printk("udp_pc_init: NO MEM\n");
	fprintf(stderr,"udp_pc_init: NO MEM\n");

g_udp_stat.snd_buff	= (u8*)malloc(MAX_FRAME_LEN);
if(g_udp_stat.snd_buff == NULL )
	fprintf(stderr,"udp_pc_init(): NO MEM FOR SND_BUF\n");
g_udp_stat.t_snd_buff1	= (u8*)malloc(MAX_FRAME_LEN);
if(g_udp_stat.t_snd_buff1 == NULL )
	fprintf(stderr,"udp_pc_init(): NO MEM FOR SND_BUF\n");
g_udp_stat.t_snd_buff2	= (u8*)malloc(MAX_FRAME_LEN);
if(g_udp_stat.t_snd_buff2 == NULL )
	fprintf(stderr,"udp_pc_init(): NO MEM FOR SND_BUF\n");
}
///=====================================
////extern void set_rec_param(u8* ibuf);
////extern int savePar(u8 nPar);
///=====================================
void dump_par_contr(void)
{
printf("\n ===== dump=====\n");
///printf("\n ===== vdp [%x:%x]\n",curr_par_contr.vdp_par.on_off,curr_par_contr.vdp_par.speed);
////printf("\n ===== izm [%x:%x]\n",curr_par_contr.izm_par.num_tacts,curr_par_contr.izm_par.num_izm);
////printf("\n ===== trk_par [%x:%x:%x:%x]\n",curr_par_contr.trk_par.num_tacts,curr_par_contr.trk_par.num_us
////					,curr_par_contr.trk_par.num_gen,curr_par_contr.trk_par.num_pow);

}
///=====================================
////extern pthread_mutex_t mutex_send_queue;

u8 *zbuf1=NULL;
///extern int set_master_slave(u8 i_dat);
///extern void init_adc(void);

int pc_set_rec_dat(u8 cmd,void *in_buf)
{
u8 *bbuf= (u8 *)in_buf;
u16 num_bytes;
///u8 t_byte;
///u16 offs;
u16 n_bytes;
///u16 tmp;
////u8 t_dat[3];
///+++++++++++++++++++++++++++++++++++++
fprintf(stderr,"\n =====new cmd =%x=======",cmd);

switch(cmd)
	{
	case NUM_WR_N_PAR_CMD:
///???		set_rec_param(in_buf);
		break;
	case NUM_SEND_XIL_DAT:
#if 1
	{
		xil_dat_req_t t_xil_dat;
		num_bytes= (*(bbuf+0))|(*(bbuf+1)<<8);
		n_bytes=MIN(num_bytes,sizeof(xil_dat_req_t));
		memcpy(&t_xil_dat,bbuf+2,n_bytes);
		puts_xil_dat(&t_xil_dat);
	}
#endif
		break;
	case NUM_PUT_SPI_DAC_DAT:
#if 1
	{
		dac_spi_req_t t_dac_da;
		num_bytes= (*(bbuf+0))|(*(bbuf+1)<<8);
		n_bytes=MIN(num_bytes,sizeof(dac_spi_req_t));
		memcpy(&t_dac_da,bbuf+2,n_bytes);
		fprintf(stderr,"\nNNUM_PUT_SPI_DAC_DAT[%x:%x]",t_dac_da.addr,t_dac_da.data);
		ioctl( mod_fd, IOCTL_PUT_SPI_DA, &t_dac_da );
	}
#endif
		break;
#if 1
	case NUM_SEND_SPI_DAC_REQ:
		{
////		dac_spi_req_t t_dac_dat;
////		int t_addr;
////		fprintf(stderr,"\nNUM_SEND_SPI_DAC_REQ");
		num_bytes= (*(bbuf+0))|(*(bbuf+1)<<8);
		n_bytes=MIN(num_bytes,sizeof(dac_spi_req_t));
////		memcpy(&g_adc_spi_dat,bbuf+2,n_bytes);
		memcpy(&g_dac_dat,bbuf+2,n_bytes);
////		g_adc_spi_dat.addr=t_alt_dat.addr;
////		g_adc_spi_dat.data=t_alt_dat.data[0];
///		t_addr=t_dac_dat.addr;
		fprintf(stderr,"\nNUM_SEND_SPI_DAC_REQ[%x]",g_dac_dat.addr);
		ioctl( mod_fd, IOCTL_SET_SPI_DA_REQ, &g_dac_dat );
		fprintf(stderr,"\nNUM_SEND_SPI_DAC_REQ1[%x:%x]",g_dac_dat.addr,g_dac_dat.data);
		}
///		get_req_spi_adc(&g_adc_spi_dat);
		break;
#endif
	case NUM_SEND_XIL_REQ:
#if 1
		fprintf(stderr,"\nNUM_SEND_XIL_REQ");
		num_bytes= (*(bbuf+0))|(*(bbuf+1)<<8);
		n_bytes=MIN(num_bytes,sizeof(xil_dat_req_t));
		memcpy(&g_xil_dat,bbuf+2,n_bytes);
		ioctl( mod_fd, IOCTL_SET_XIL_REQ, &g_xil_dat );
////		ioctl( mod_trk_fd, IOCTL_SET_ALT_REQ, &g_alt_dat );
////		printf("\nNUM_SEND_ALT_REQ1[%x:%x:%x]",g_alt_dat.addr
///				,g_alt_dat.ndata,g_alt_dat.data[0]);
#endif
		break;
	}
return 0;
}
////extern void tst_print_dat1(rez_amp_bl_t *dat_rez);
////extern u8 flg_req_osc;
extern volatile u8 tst_t;

extern void set_tst_oscs(u8 idat);

u16	pc_get_req_dat(u8 num_req,u8 *buf)
{
u16 rez=0;
switch(num_req)
	{
	case NUM_GET_SPI_ADC_DAT:
#if 0
		{
		int t_dat;
		fprintf(stderr,"\nNUM_GET_SPI_ADC_DAT");
		if( ioctl( mod_trk_fd, IOCTL_GET_SPI_ADC, (void*)&t_dat ) >=0)
			{
			memcpy(buf,&t_dat,sizeof(int));
			rez=sizeof(int);
			fprintf(stderr,"[%x]\n",t_dat);

	////		printf("\nNUM_REQ_ALT_DAT[%x:%x:%x]",t_alt_dat_req.addr
	////				,t_alt_dat_req.ndata,t_alt_dat_req.data[0]);
			}
		else
		{
	///		printf("\nerr=NUM_REQ_ALT_DAT[%x:%x:%x]",t_alt_dat_req.addr
	///				,t_alt_dat_req.ndata,t_alt_dat_req.data[0]);
			rez=0;
		}
	}
#endif
		break;
	case NUM_REQ_XIL_DAT:
#if 1
	{
	xil_dat_req_t t_xil_dat_req;
	if( ioctl( mod_fd, IOCTL_GET_XIL_DATA, (void*)&t_xil_dat_req ) >=0)
		{
		memcpy(buf,&t_xil_dat_req,sizeof(xil_dat_req_t));
		rez=sizeof(xil_dat_req_t);
///		fprintf(stderr,"\n\rNUM_REQ_XIL_DAT[%x:%x:%x]",t_alt_dat_req.addr
///				,t_alt_dat_req.ndata,t_alt_dat_req.data[0]);
		}
	else
		{
	///	printf("\nerr=NUM_REQ_ALT_DAT[%x:%x:%x]",t_alt_dat_req.addr
	////			,t_alt_dat_req.ndata,t_alt_dat_req.data[0]);
		rez=0;
		}
		fprintf(stderr,"\nNUM_REQ_XIL_DAT");
	}
#endif
		break;
	case NUM_GET_SPI_DAC_DAT:
#if 1
		{
		dac_spi_req_t t_dac_spi_req;
		if( ioctl( mod_fd, IOCTL_GET_SPI_DA_DATA, (void*)&t_dac_spi_req ) >=0)
			{
			memcpy(buf,&t_dac_spi_req,sizeof(dac_spi_req_t));
			rez=sizeof(dac_spi_req_t);
			fprintf(stderr,"\nNUM_GET_SPI_DAC_DAT[%x:%x]",t_dac_spi_req.addr
				,t_dac_spi_req.data);
			}
	else
		{
///		printf("\nerr=NUM_REQ_ACT_DAT[%x:%x:%x]",t_alt_dat_req.addr
///				,t_alt_dat_req.ndata,t_alt_dat_req.data[0]);
		rez=0;
		}
	}
#endif
		break;
	case NUM_REQ_GET_OSC0:
#if 0
		set_tst_oscs(tst_t);
		tst_t += 3;

		memcpy(buf, buffOscs[0],LEN_OSC);
		rez=LEN_OSC;
////		flg_req_osc=1;
////		fprintf(stderr,"<");
		break;
	case NUM_REQ_GET_OSC1:
		memcpy(buf, buffOscs[1],LEN_OSC);
#endif
		rez=LEN_OSC;
////		flg_req_osc=1;
		break;
	case NUM_REQ_GET_AMPS:
#if 0
		{
		static int tcnt=0;
///		int ii;
///		int cnt_bytes=0;
		amp_buff_bl_t t_rez_amp_bl;
		cnt=queue_size(&queue_rez);
		if((cnt==0)||(cnt<SND_CNT_REZ))
			{
			t_rez_amp_bl.cnt=0;
			memcpy(buf,&t_rez_amp_bl,sizeof(amp_buff_bl_t));
			rez=sizeof(amp_buff_bl_t);
////			rez=1;
			}
		else
			{
			int ii;
			offs=1;
			if(cnt>MAX_CNT_REZ)
			{
			fprintf(stderr,"\n!!!cnt>MAX_CNT_REZ[%d:%d]!!!!\n",cnt,sizeof(rez_amp_bl_t));
///			cnt=MAX_CNT_REZ;
			}
			cnt=SND_CNT_REZ;
			memcpy(buf,&cnt,sizeof(uint8_t));
				for(ii=0;ii<cnt;ii++)
				{
				tcnt++;
				queue_dequeue(&queue_rez,(void*)&t_rez_amp_bl.ampl_bl);
				memcpy(buf+offs,&t_rez_amp_bl.ampl_bl,sizeof(rez_amp_bl_t));
				offs+=sizeof(rez_amp_bl_t);
#if 0
				if(t_rez_amp_bl.ampl_bl.ampl_tact[0].ampl_us[6].ampl_str[0].ampl<128)
					{
					fprintf(stderr,"\n!ampl[%d:%d][%d:%d][%d] "
							,t_rez_amp_bl.ampl_bl.ampl_tact[0].ampl_us[6].ampl_str[0].ampl
							,t_rez_amp_bl.ampl_bl.ampl_tact[0].ampl_us[6].ampl_str[1].ampl
							,t_rez_amp_bl.ampl_bl.ampl_tact[0].ampl_us[6].ampl_str[0].time
							,t_rez_amp_bl.ampl_bl.ampl_tact[0].ampl_us[6].ampl_str[1].time
							,tcnt);
					}
#endif
				}
////			tst_print_dat1((rez_amp_bl_t*)&t_rez_amp_bl.ampl_bl);
			rez=offs;
			}
		}
#endif
		break;
	default:
		rez=0;
		break;
	}
return rez;
}
