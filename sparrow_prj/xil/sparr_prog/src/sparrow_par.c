#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include "../../common_inc/sparrow_types.h"
#include "../../common_inc/sparrow_ioctl.h"
#include "./inc/sparrow_cnf.h"
#include "../../common_inc/sparrow_fpga_mm.h"
#include "./inc/sparrow_udp_cmds.h"
extern int put_kus_adc(uint16_t i_val);
extern int put_rele(uint8_t i_val);

uint32_t g_changed_param=0;
static uint16_t param_num_bytes;
uint8_t t_par_buff[1000];

void set_changed_param(void)
{
uint16_t t_offs=sizeof(u32);
uint16_t tmp_dat;
///fprintf(stderr,"\n===_set_changed_param[%x]====\n",g_changed_param);
if(g_changed_param&CHNG_TIMP_LEN)
	{
	memcpy(&tmp_dat,t_par_buff+t_offs,sizeof(uint16_t));
///	set_len(tmp_dat);
	t_offs+=sizeof(u16);
	///fprintf(stderr,"\n===CHNG_TIMP_LEN[%x]====",tmp_dat);
	g_changed_param&=~CHNG_TIMP_LEN;
	}
if(g_changed_param&CHNG_TIMP_OFFSET)
	{
	memcpy(&tmp_dat,t_par_buff+t_offs,sizeof(u16));
///	set_delay(tmp_dat);
	t_offs+=sizeof(u16);
	g_changed_param&=~CHNG_TIMP_OFFSET;
	}
if(g_changed_param&CHNG_TCYCLE)
	{
	memcpy(&tmp_dat,t_par_buff+t_offs,sizeof(u16));
///	set_range(tmp_dat);
	t_offs+=sizeof(u16);
	///fprintf(stderr,"\n===CHNG_TCYCLE[%x]====",tmp_dat);
	g_changed_param&=~CHNG_TCYCLE;
	}
if(g_changed_param&CHNG_TDEF)
	{
	memcpy(&tmp_dat,t_par_buff+t_offs,sizeof(u16));
///	set_len_def(tmp_dat);
	t_offs+=sizeof(u16);
	///fprintf(stderr,"\n===CHNG_TDEF[%x]====",tmp_dat);
	g_changed_param&=~CHNG_TDEF;
	}
if(g_changed_param&CHNG_IMP_POINTS)
	{
	memcpy(&tmp_dat,t_par_buff+t_offs,sizeof(u16));
///	set_len(tmp_dat);
	t_offs+=sizeof(u16);
////	memcpy(gen_buf,t_par_buff+t_offs,sizeof(u16)*tmp_dat);
	t_offs+=sizeof(u16)*tmp_dat;
///	set_gen_dat(gen_buf,tmp_dat);
	///fprintf(stderr,"\n===CHNG_IMP_POINTS[%x]====",tmp_dat);
	g_changed_param&=~CHNG_IMP_POINTS;
	}
#if 0
if(g_changed_param&CHNG_PRESC)
	{
	memcpy(&tmp_dat,t_par_buff+t_offs,sizeof(u16));
	set_prescale(tmp_dat);
	t_offs+=sizeof(u16);
	fprintf(stderr,"\n===CHNG_PRESC[%x]====",tmp_dat);
	g_changed_param&=~CHNG_PRESC;
	}
#endif
if(g_changed_param&CHNG_KUS)
	{
	memcpy(&tmp_dat,t_par_buff+t_offs,sizeof(u16));
	put_kus_adc(tmp_dat<<4);
	t_offs+=sizeof(u16);
	///fprintf(stderr,"\n===CHNG_KUS[%x]====",tmp_dat);
	g_changed_param&=~CHNG_KUS;
	}
if(g_changed_param&CHNG_ATT)
	{
	uint8_t btmp;
	memcpy(&btmp,t_par_buff+t_offs,sizeof(uint8_t));
	btmp&=0x3;
	put_rele(btmp^0x3);
	////set_delay(tmp_dat);
	t_offs+=sizeof(uint8_t);
	///fprintf(stderr,"\n===CHNG_ATT[%x]====",btmp);
	g_changed_param&=~CHNG_ATT;
	}


if(g_changed_param&CHNG_BSTRB)
	{
	memcpy(&tmp_dat,t_par_buff+t_offs,sizeof(u16));
	////set_delay(tmp_dat);
	t_offs+=sizeof(u16);
	g_changed_param&=~CHNG_BSTRB;
	}
if(g_changed_param&CHNG_LSTRB)
	{
	memcpy(&tmp_dat,t_par_buff+t_offs,sizeof(u16));
	////set_len(tmp_dat);
	t_offs+=sizeof(u16);
	///fprintf(stderr,"\n===CHNG_LSTRB[%x]====",tmp_dat);
	g_changed_param&=~CHNG_LSTRB;
	}
if(g_changed_param&CHNG_PRE)
	{
	memcpy(&tmp_dat,t_par_buff+t_offs,sizeof(u16));
	////set_prescale(tmp_dat);
	t_offs+=sizeof(u16);
	///fprintf(stderr,"\n===CHNG_PRE[%x]====",tmp_dat);
	g_changed_param&=~CHNG_PRE;
	}
if(g_changed_param&CHNG_RNG)
	{
	memcpy(&tmp_dat,t_par_buff+t_offs,sizeof(u16));
	///set_range(tmp_dat);
	t_offs+=sizeof(u16);
	///fprintf(stderr,"\n===CHNG_RNG[%x]====",tmp_dat);
	g_changed_param&=~CHNG_RNG;
	}
if(g_changed_param&CHNG_LEN_DEF)
	{
	memcpy(&tmp_dat,t_par_buff+t_offs,sizeof(u16));
	///set_len_def(tmp_dat);
	t_offs+=sizeof(u16);
	///fprintf(stderr,"\n===CHNG_LEN_DEF[%x]====",tmp_dat);
	g_changed_param&=~CHNG_LEN_DEF;
	}
if(g_changed_param&CHNG_FORM)
	{
	memcpy(&tmp_dat,t_par_buff+t_offs,sizeof(u16));
///	set_len(tmp_dat);
	t_offs+=sizeof(u16);
	///fprintf(stderr,"\n===CHNG_FORM[%x]====",tmp_dat);
	g_changed_param&=~CHNG_FORM;
	}
if(g_changed_param)
	fprintf(stderr,"\n??CHNG_PAR??[%x]====",g_changed_param);
g_changed_param=0;
}




void set_rec_param(u8* ibuf)
{
///u16 num_bytes1;
///uint32_t tmp;
param_num_bytes= (*ibuf)|(*(ibuf+1)<<8);
///num_bytes1= (*(ibuf+2))|(*(ibuf+3)<<8);

memcpy(&g_changed_param,ibuf+4,sizeof(u32));
memcpy(t_par_buff,ibuf+4,param_num_bytes);
}
