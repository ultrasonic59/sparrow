/*
 * udac.c
 *
 *  Created on: Jan 17, 2020
 *      Author: vovag
 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <math.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h> // I2C bus definitions
#include "../../common_inc/sparrow_fpga_mm.h"

extern int fd_i2c;
extern volatile void *fpga_regs;
volatile uint16_t  *g_dac_mem = NULL;

uint16_t t_sin_buff[SIN_BUFF_SIZE];

void set_gen_dat(uint16_t *ibuf,int len)
{
int ii;
///uint16_t htmp;
#if 1
g_dac_mem = (uint16_t *)(fpga_regs +
		DAC_RAM_OFFSET);
for(ii = 0; ii < len; ii++)
	{
///	htmp=ibuf[ii];
///	g_dac_mem[ii] = htmp;
	g_dac_mem[ii] = (int16_t)ibuf[ii];
	}
#endif
#if 0
uint16_t htmp;
g_dac_mem = (uint16_t *)(fpga_regs);
fprintf(stderr,"\n\r");

for(ii = 0; ii < 8; ii++)
	{
	htmp=g_dac_mem[ii] ;
	fprintf(stderr,"[%x] ",htmp) ;
	}
#endif
}
uint16_t get_dac_reg_dat(uint16_t i_offs)
{
uint16_t rez;

g_dac_mem = (uint16_t *)(fpga_regs +
		DAC_REG_OFFSET);
rez=g_dac_mem[i_offs] ;
return rez;
}
uint16_t get_dac_ram_dat(uint16_t i_offs)
{
uint16_t rez;

g_dac_mem = (uint16_t *)(fpga_regs +
		DAC_RAM_OFFSET);
rez=g_dac_mem[i_offs] ;
return rez;
}
#define M 8191
#define N 8191

int init_sin_table(void)
{
int ii;
double t_fl=5.0;
for(ii=0;ii<SIN_BUFF_SIZE;ii++)
	{
	t_fl=(M*(1.0+sin((2*M_PI*ii)/N)))/2;
	t_sin_buff[ii]=(uint16_t)t_fl;
	}

/*
for(ii=0;ii<SIN_BUFF_SIZE;ii++)
	{
	t_sin_buff[ii]=(uint16_t)ii;
	}
	*/
return 0;
}
const int urele_address = 0x30;

int put_rele(uint8_t i_val)
{
uint8_t writeBuf[1];
///fprintf(stderr,"put_rele[%x]!\n",i_val);

if (ioctl(fd_i2c, I2C_SLAVE, urele_address) < 0)
	{
    fprintf(stderr,"Error: Couldn't find device on address[%x]!\n",urele_address);
	return -1;
	}
 else
  {
	 writeBuf[0]=i_val&0x3;
	if (write(fd_i2c,writeBuf,1) != 1)
		{
	    fprintf(stderr,"Err:Failed to write to the i2c bus[rele].\n");
		return -2;
		}
	}
return 0;
}

