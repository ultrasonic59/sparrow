#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include "./inc/rp_ugen_cnf.h"
#include "./inc/my_types.h"
#include "./inc/udp_types.h"
#include "./inc/udp_cmds.h"
#include "./inc/ugen_fpga.h"
///=================================================
///extern volatile ugen_reg_t *ugen_regs;
extern volatile void *fpga_regs;
#define OFFS_DELAY_A	0x1c
///u8 *t_par_buff;
u8 t_par_buff[1000];
static u16 param_num_bytes;
u32 g_changed_param=0;
void set_delay(uint32_t idat)
{
ugen_reg_t *ugen_regs=(ugen_reg_t *)fpga_regs;
ugen_regs->delay_a=idat;
///	fprintf(stderr,"\nset_delay[%x:%x] ",idat,(uint32_t)&ugen_regs->delay_a);
}
extern void calc_sin(int32_t *data,int16_t num);
extern void set_gen_dat(uint16_t *ibuf,int len);
uint16_t gen_buf[64000];

void set_len(uint32_t idat)
{
	int t_num;
ugen_reg_t *ugen_regs=(ugen_reg_t *)fpga_regs;
///	fprintf(stderr,"\nset_len[%x:%x] ",idat,(uint32_t)&ugen_regs->len_a);
/////ugen_regs->len_a= idat;
t_num = idat/NUM_PNT_SIN;
///calc_sin(gen_buf,t_num);
///set_gen_dat(gen_buf,t_num*NUM_PNT_SIN);
ugen_regs->len_a= t_num*NUM_PNT_SIN;
}
void set_prescale(uint32_t idat)
{
ugen_reg_t *ugen_regs=(ugen_reg_t *)fpga_regs;
ugen_regs->pre=idat;
	fprintf(stderr,"\nset_prescale[%x:%x] ",idat,(uint32_t)&ugen_regs->pre);
}
void set_range(uint32_t idat)
{
ugen_reg_t *ugen_regs=(ugen_reg_t *)fpga_regs;
ugen_regs->rng=idat;
	fprintf(stderr,"\nset_range[%x:%x] ",idat,(uint32_t)&ugen_regs->rng);
}
void set_len_def(uint32_t idat)
{
ugen_reg_t *ugen_regs=(ugen_reg_t *)fpga_regs;
ugen_regs->len_def=idat;
	fprintf(stderr,"\nset_len_def[%x:%x] ",idat,(uint32_t)&ugen_regs->len_def);
}

void set_rec_param(u8* ibuf)
{
u16 num_bytes1;
uint32_t tmp;
param_num_bytes= (*ibuf)|(*(ibuf+1)<<8);
num_bytes1= (*(ibuf+2))|(*(ibuf+3)<<8);

memcpy(&g_changed_param,ibuf+4,sizeof(u32));
///memcpy(&tmp,ibuf+4,sizeof(u32));
///g_changed_param=tmp;
memcpy(t_par_buff,ibuf+4,param_num_bytes);
////fprintf(stderr,"\nset_rec_param g_changed_param[%lx]:num_bytes1[%x]",g_changed_param,num_bytes1);
////set_changed_param();
}


void set_changed_param(void)
{
long len;
u32 t_changed_param=0;
uint16_t tmp_dat;
u16 num_bytes=0;
u16 t_offs=sizeof(u32);
fprintf(stderr,"\n===_set_changed_param[%lx]====\n",g_changed_param);
if(g_changed_param&CHNG_TIMP_LEN)
	{
	memcpy(&tmp_dat,t_par_buff+t_offs,sizeof(u16));
	set_len(tmp_dat);
	t_offs+=sizeof(u16);
	fprintf(stderr,"\n===CHNG_TIMP_LEN[%x]====",tmp_dat);
	g_changed_param&=~CHNG_TIMP_LEN;
	}
if(g_changed_param&CHNG_TIMP_OFFSET)
	{
	memcpy(&tmp_dat,t_par_buff+t_offs,sizeof(u16));
	set_delay(tmp_dat);
	t_offs+=sizeof(u16);
	g_changed_param&=~CHNG_TIMP_OFFSET;
	}
if(g_changed_param&CHNG_TCYCLE)
	{
	memcpy(&tmp_dat,t_par_buff+t_offs,sizeof(u16));
	set_range(tmp_dat);
	t_offs+=sizeof(u16);
	fprintf(stderr,"\n===CHNG_TCYCLE[%x]====",tmp_dat);
	g_changed_param&=~CHNG_TCYCLE;
	}
if(g_changed_param&CHNG_TDEF)
	{
	memcpy(&tmp_dat,t_par_buff+t_offs,sizeof(u16));
	set_len_def(tmp_dat);
	t_offs+=sizeof(u16);
	fprintf(stderr,"\n===CHNG_TDEF[%x]====",tmp_dat);
	g_changed_param&=~CHNG_TDEF;
	}
if(g_changed_param&CHNG_IMP_POINTS)
	{
	memcpy(&tmp_dat,t_par_buff+t_offs,sizeof(u16));
///	set_len(tmp_dat);
	t_offs+=sizeof(u16);
	memcpy(gen_buf,t_par_buff+t_offs,sizeof(u16)*tmp_dat);
	t_offs+=sizeof(u16)*tmp_dat;
	set_gen_dat(gen_buf,tmp_dat);
	fprintf(stderr,"\n===CHNG_IMP_POINTS[%x]====",tmp_dat);
	g_changed_param&=~CHNG_IMP_POINTS;
	}
if(g_changed_param&CHNG_PRESC)
	{
	memcpy(&tmp_dat,t_par_buff+t_offs,sizeof(u16));
	set_prescale(tmp_dat);
	t_offs+=sizeof(u16);
	fprintf(stderr,"\n===CHNG_PRESC[%x]====",tmp_dat);
	g_changed_param&=~CHNG_PRESC;
	}

if(g_changed_param&CHNG_BSTRB)
	{

	memcpy(&tmp_dat,t_par_buff+t_offs,sizeof(u16));
	set_delay(tmp_dat);
	t_offs+=sizeof(u16);
	g_changed_param&=~CHNG_BSTRB;
	}
if(g_changed_param&CHNG_LSTRB)
	{
	memcpy(&tmp_dat,t_par_buff+t_offs,sizeof(u16));
	set_len(tmp_dat);
	t_offs+=sizeof(u16);
	fprintf(stderr,"\n===CHNG_LSTRB[%x]====",tmp_dat);
	g_changed_param&=~CHNG_LSTRB;
	}
if(g_changed_param&CHNG_PRE)
	{
	memcpy(&tmp_dat,t_par_buff+t_offs,sizeof(u16));
	set_prescale(tmp_dat);
	t_offs+=sizeof(u16);
	fprintf(stderr,"\n===CHNG_PRE[%x]====",tmp_dat);
	g_changed_param&=~CHNG_PRE;
	}
if(g_changed_param&CHNG_RNG)
	{
	memcpy(&tmp_dat,t_par_buff+t_offs,sizeof(u16));
	set_range(tmp_dat);
	t_offs+=sizeof(u16);
	fprintf(stderr,"\n===CHNG_RNG[%x]====",tmp_dat);
	g_changed_param&=~CHNG_RNG;
	}
if(g_changed_param&CHNG_LEN_DEF)
	{
	memcpy(&tmp_dat,t_par_buff+t_offs,sizeof(u16));
	set_len_def(tmp_dat);
	t_offs+=sizeof(u16);
	fprintf(stderr,"\n===CHNG_LEN_DEF[%x]====",tmp_dat);
	g_changed_param&=~CHNG_LEN_DEF;
	}
if(g_changed_param&CHNG_FORM)
	{
	memcpy(&tmp_dat,t_par_buff+t_offs,sizeof(u16));
///	set_len(tmp_dat);
	t_offs+=sizeof(u16);
	fprintf(stderr,"\n===CHNG_FORM[%x]====",tmp_dat);
	g_changed_param&=~CHNG_FORM;
	}

g_changed_param=0;
}