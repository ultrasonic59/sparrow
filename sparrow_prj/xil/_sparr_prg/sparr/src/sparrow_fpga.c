/*
 * sparrow_fpga.c
 *
 *  Created on: Au 6, 2019
 *      Author: vovag
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
#include "./inc/sparrow_fpga.h"
extern int mod_fd;

xil_dat_req_t g_xil_dat;
dac_spi_req_t g_dac_dat;


int init_dac(uint8_t idat)
{
int tmp=idat;
ioctl( mod_fd, IOCTL_INIT_DA, &tmp );
fprintf(stderr,"\n init_dac[%x] ",idat);

return 0;
}
int set_spd_spi(uint8_t idat)
{
int tmp=idat;
ioctl( mod_fd, IOCTL_SET_SPD_SPI_ADDA, &tmp );
fprintf(stderr,"\n set_spd_spi[%x] ",idat);

return 0;
}
///=================================
int puts_spi_adc_dat(adc_spi_req_t *ad_spi_req)
{
#if 0
	uint32_t *ptbuff;
	ptbuff=(uint32_t *)ugen_regs;
///return put_spi_adc_dat(ad_spi_req->addr,ad_spi_req->data);
///	ugen_regs->pre=	ad_spi_req->
	ptbuff[ad_spi_req->addr]=ad_spi_req->data;
#endif
	return 0;
}
///=================================
int puts_xil_dat(xil_dat_req_t *xil_req)
{
ioctl( mod_fd, IOCTL_SET_XIL_DATA, xil_req );
fprintf(stderr,"\n puts_xil_dat[%x:%x] ",xil_req->addr,xil_req->data[0]);
return 0;
}
///=================================
int gets_xil_dat(xil_dat_req_t *xil_req)
{
#if 0
	uint8_t *ptbuff;
	ptbuff=(uint8_t *)fpga_regs;
	memcpy(xil_req,&g_xil_dat,sizeof(xil_dat_req_t));
	xil_req->data[0]=*((uint32_t*)(ptbuff+xil_req->addr));
	fprintf(stderr,"\ngets_xil_dat[%x:%x] ",xil_req->addr,xil_req->data[0]);
#endif
	return 0;
}

///============================================



