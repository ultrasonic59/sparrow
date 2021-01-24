/*
 * ugen_fpga.c
 *
 *  Created on: Apr 8, 2017
 *      Author: vovag
 */
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

#include "./inc/ugen_fpga.h"

///volatile ugen_reg_t *ugen_regs;
volatile void *fpga_regs;
volatile uint32_t  *g_awg_cha_mem = NULL;

///g_awg_cha_mem = (uint32_t *)g_awg_reg +
////    (AWG_CHA_OFFSET / sizeof(uint32_t));
void set_gen_dat(uint16_t *ibuf,int len)
{
int ii;
g_awg_cha_mem = (uint32_t *)(fpga_regs +
    AWG_CHA_OFFSET);
for(ii = 0; ii < len; ii++) {
    g_awg_cha_mem[ii] = 8191-(int16_t)ibuf[ii];
}

}
int init_ugen_fpga(void)
{
	int ii;
int mem_file;
if((mem_file = open("/dev/mem", O_RDWR)) < 0)
	  {
	  perror("open mem_file");
	  return 1;
	  	  }
///ugen_regs = (ugen_reg_t *)mmap(NULL, sysconf(_SC_PAGESIZE), PROT_READ|PROT_WRITE, MAP_SHARED, mem_file, UGEN_BASE_ADDR);
///fpga_regs = mmap(NULL, sysconf(_SC_PAGESIZE), PROT_READ|PROT_WRITE, MAP_SHARED, mem_file, UGEN_BASE_ADDR);
fpga_regs = mmap(NULL, UGEN_BASE_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, mem_file, UGEN_BASE_ADDR);
////g_awg_cha_mem = (uint32_t *)fpga_regs +
///    (AWG_CHA_OFFSET / sizeof(uint32_t));
///g_awg_cha_mem = (uint32_t *)(fpga_regs +
///    AWG_CHA_OFFSET);

///for(ii = 0; ii < n; ii++) {
///    g_awg_cha_mem[ii] = ii;
////}
return 0;
}



