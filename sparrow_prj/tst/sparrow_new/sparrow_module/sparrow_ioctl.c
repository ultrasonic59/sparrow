/*
 * sepia_trk_ioctl.c
 *
 *  Created on: 07 7, 2015
 *      Author: vovag
 */

#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/slab.h>
#include <linux/input.h>
#include <linux/init.h>
#include <linux/serio.h>
#include <linux/delay.h>
#include <linux/clk.h>
#include <linux/miscdevice.h>
#include <linux/timer.h>
#include <linux/param.h>
#include <linux/poll.h>
#include <linux/proc_fs.h>
#include <linux/err.h>
#include <linux/io.h>
///++++++++++++++++++++++++++++++++++++++++
///#include <asm/io.h>
////#include <plat/gpio-cfg.h>

///#include <asm/system.h>
#include <asm/mach-types.h>

///#include <asm/irq.h>
///#include <mach/map.h>
////#include <plat/cpu.h>

#include <asm/io.h>
#include <linux/gpio.h>

#////include <asm/irq.h>
#if 0
#include <mach/regs-gpio.h>
#include <mach/gpio-bank-a.h>
#include <mach/gpio-bank-b.h>
#include <mach/gpio-bank-k.h>
#include <mach/gpio-bank-n.h>
#endif

#include "sparrow_drv.h"
#include "../common_inc/sparrow_types.h"

#include "../common_inc/sparrow_ioctl.h"
///#include "../common_inc/sepia_types.h"
///#include "../common_inc/sepia_utrk.h"
///#include "../common_inc/sepia_fpga_mm.h"
////#include "sepia_mod_type.h"

#define MAX_CNT_WAIT 		10000


///+++++++++++++++++++++++++++++++++++++++++
extern struct gpio rst_dac;

extern unsigned long sparrow_base;

////extern ed_par_trk_t ed_par_trk;
extern char vers_str[];
///+++++++++++++++++++++++++++++++++++++++
#if 0
unsigned long vdelay(unsigned long idel)
{
unsigned long rez=1;
unsigned long ii;
for(ii=0;ii<idel;ii++)
{
rez*= rez+1;
}
return rez;
}
#endif

uint16_t rd_dat_fpga(uint16_t addr)
{
uint16_t rez;
uint16_t *udef_addr=(uint16_t*)sparrow_base;
rez= *(udef_addr+addr);
return rez;
}

void wr_dat_fpga(uint16_t addr,uint16_t dat)
{
volatile uint16_t *udef_addr=(uint16_t*)sparrow_base;
///printk( KERN_ERR "\n=== [mod]wr_dat_fpga[%x:%x]",addr,dat );
*(udef_addr+addr)=dat;
///printk( KERN_ERR "\n=== [mod]wr_dat_fpga1[%x:%x]",addr,dat );

}
uint32_t rd_dat32_fpga(uint16_t addr)
{
uint32_t rez;
uint16_t tmp;
uint16_t *udef_addr=(uint16_t*)sparrow_base;
tmp= *(udef_addr+addr);
rez= *(udef_addr+addr+2);
rez<<=16;
rez|=tmp;
return rez;
}
void rd_dat_blok_fpga(uint16_t addr,uint16_t len,uint16_t *obuf)
{
uint16_t ii=0;
uint16_t t_dat;
uint16_t *udef_addr=(uint16_t*)sparrow_base;
///spi1_mutex_lock();
////len=64;
for(ii=0;ii<len;ii++)
	{
	t_dat=*(udef_addr+addr+ii);
	*(obuf+ii)=t_dat;
	}

///spi1_mutex_unlock();
}
void rd_osc_(uint16_t addr_osc,uint16_t len,uint8_t *obuf)
{
uint16_t ii;
uint16_t *t_buf=(uint16_t*)obuf;
uint16_t t_dat;
uint16_t *udef_addr=(uint16_t*)sparrow_base;
///spi1_mutex_lock();
for(ii=0;ii<(len/2);ii++)
	{
	t_dat=*(udef_addr+addr_osc+ii);
	*(t_buf+ii)=t_dat;
	}
///spi1_mutex_unlock();
}

void wr_dat32_fpga(uint16_t addr,uint32_t dat)
{
uint16_t *udef_addr=(uint16_t*)sparrow_base;
///	 spi1_mutex_lock();
*(udef_addr+addr)=dat&0xffff;
*(udef_addr+addr+2)=(dat>>16)&0xffff;
///spi1_mutex_unlock();
}
void wr_dat_blok_fpga(uint16_t addr,uint16_t len,uint16_t *ibuf)
{
uint16_t ii;
uint16_t *udef_addr=(uint16_t*)sparrow_base;
///spi1_mutex_lock();
for(ii=0;ii<len;ii++)
	{
	*(udef_addr+addr+ii) = *(ibuf+ii);
	}
///spi1_mutex_unlock();
}

///=========================================

void clr_ext_irq(void)
{
////static int for_test=0;
///iowrite16(0x1, weasel_trk_base+ADDR_CLR_IRQ);
///wr_dat_trk(ADDR_UG_CLR_IRQ,0x1);
///for_test++;
}

///==========================
void set_spd_spi_adda(unsigned char idat)
{
wr_dat_fpga(ADDR_SPD_SPI,idat);
printk( KERN_ERR "\n\r=== [mod]set_spd_spi_adda[%x]===",idat);

}
#define MAX_READY_CNT 20000

#define DELAY_SPI_ADDA 10000

int wait_ready_spi_adda(void)
{
int cnt_ready=0;
uint16_t t_dat;
for(cnt_ready=0;cnt_ready<MAX_READY_CNT;cnt_ready++)
	{
	t_dat=rd_dat_fpga(ADDR_SPI_RDY);
	if((t_dat&SPI_BUSY_BIT)==0)
		break;
	udelay(2);
	}
if(cnt_ready<MAX_READY_CNT)
	return 0;
else
	return -1;
}

int mod_put_spi_da(u8 i_addr,u16 i_data)
{
int rdy;
rdy=wait_ready_spi_adda();
///printk( KERN_ERR "\n\r=== [mod]put_spi_da[%x:%x[%d]]===",i_addr,i_data,rdy );

if(rdy!=0)
	return rdy;
wr_dat_fpga(ADDR_SPI_CS_A,0x0);///ncs=0
i_addr&=0x7f;///write
wr_dat_fpga(ADDR_SPI_WR_DATA,i_addr);
rdy=wait_ready_spi_adda();
///printk( KERN_ERR "\n\r=== [mod]put_spi_da2[%x:%x[%d]]===",i_addr,i_data,rdy );
if(rdy!=0)
	{
	wr_dat_fpga(ADDR_SPI_CS_A,0x1);
	return rdy;
	}
wr_dat_fpga(ADDR_SPI_WR_DATA,i_data>>8);
rdy=wait_ready_spi_adda();
///printk( KERN_ERR "\n\r=== [mod]put_spi_da3[%x:%x[%d]]===",i_addr,i_data,rdy );
if(rdy!=0)
	{
	wr_dat_fpga(ADDR_SPI_CS_A,0x1);
	return rdy;
	}
wr_dat_fpga(ADDR_SPI_WR_DATA,i_data&0xff);
rdy=wait_ready_spi_adda();
///printk( KERN_ERR "\n\r=== [mod]put_spi_da4[%x:%x[%d]]===",i_addr,i_data,rdy );
///if(rdy!=0)
///	{
///	wr_dat_fpga(ADDR_SPI_CS_A,0x1);
///	return rdy;
////	}
///printk( KERN_ERR "\n\r=== [mod]put_spi_da5[%x:%x[%d]]===",i_addr,i_data,rdy );
wr_dat_fpga(ADDR_SPI_CS_A,0x1);
///printk( KERN_ERR "\n\r=== [mod]put_spi_da5a[%x:%x[%d]]===",i_addr,i_data,rdy );
return rdy;
}
int mod_get_spi_da(u8 i_addr,u16 *odata )
{
int rdy;
u16 rez;
u16 _tst;
rdy=wait_ready_spi_adda();
if(rdy!=0)
	{
	return rdy;
	}
wr_dat_fpga(ADDR_SPI_CS_A,0x0);
i_addr|=(0x1<<7);///read
wr_dat_fpga(ADDR_SPI_WR_DATA,i_addr);///set addr
rdy=wait_ready_spi_adda();
if(rdy!=0)
	{
	wr_dat_fpga(ADDR_SPI_CS_A,0x1);
	return rdy;
	}
wr_dat_fpga(ADDR_SPI_REQ_DATA,0);
rdy=wait_ready_spi_adda();
if(rdy!=0)
	{
	wr_dat_fpga(ADDR_SPI_CS_A,0x1);
	return rdy;
	}
_tst=rd_dat_fpga(ADDR_SPI_RD_DATA);
rez=_tst&0xff;
rez<<=8;
wr_dat_fpga(ADDR_SPI_REQ_DATA,0);
rdy=wait_ready_spi_adda();
if(rdy!=0)
	{
	wr_dat_fpga(ADDR_SPI_CS_A,0x1);
	return rdy;
	}
_tst=rd_dat_fpga(ADDR_SPI_RD_DATA);
rez|= _tst&0xff;

wr_dat_fpga(ADDR_SPI_CS_A,0x1);
*odata=rez;
///printk( KERN_ERR "\n\r=== [mod]mod_get_spi_da[%x:%x[%d]]===",i_addr,rez,rdy );

return rdy;
}

///===========================================
////static alt_dat_req_t alt_dat_req;

static xil_dat_req_t xil_dat_req;
static dac_spi_req_t dac_spi_dat_req;
////static alt_dat_req_t act_dat_req;
////static adc_spi_req_t adc_spi_dat_req;
void get_spi_da_data(dac_spi_req_t *tbuff)
{
u16 tmp;

mod_get_spi_da(dac_spi_dat_req.addr,&tmp);
tbuff->data=tmp;
tbuff->addr=dac_spi_dat_req.addr;
///====================================
///printk( KERN_ERR "\n=== [mod]get_spi_da_data[%x:%x]",tbuff->addr,tbuff->data);
///=======================================
}

void get_xil_data(xil_dat_req_t *tbuff)
{
int ii;
u16 tmp;
if(xil_dat_req.ndata>MAX_XIL_DATA_LEN)
	xil_dat_req.ndata=MAX_XIL_DATA_LEN;
for(ii=0;ii<xil_dat_req.ndata;ii++)
	{
///	tmp=ioread16((void*)(octopuz_trk_base+xil_dat_req.addr+ii) );
	tmp=rd_dat_fpga(xil_dat_req.addr+ii);
	tbuff->data[ii]=tmp;
	}
tbuff->addr=xil_dat_req.addr;
tbuff->ndata=xil_dat_req.ndata;
///======================================================
///printk( KERN_ERR "\n=== [mod]get_xil_data[%x:%x]",tbuff->addr,tbuff->data[0] );
///============================================================
}
void put_xil_data(xil_dat_req_t *tbuff)
{
int ii;
if(tbuff->ndata>MAX_XIL_DATA_LEN)
	tbuff->ndata=MAX_XIL_DATA_LEN;
for(ii=0;ii<tbuff->ndata;ii++)
	{
///	iowrite16(tbuff->data[ii], (void*)(octopuz_trk_base+xil_dat_req.addr+ii));
	wr_dat_fpga(xil_dat_req.addr+ii ,tbuff->data[ii]);
	}
///======================================================
///printk( KERN_ERR "\n=== [mod]put_xil_data[%x:%x]",xil_dat_req.addr,tbuff->data[0] );
///============================================================
}
void put_rst_dac(int on_off)
{
int value=0;
#if 1
if(on_off&0x1)
	value=1;
////	XGpioPs_WritePin(&Gpio, RST_DAC_PIN, 0x1);
else
	value=0;
////	XGpioPs_WritePin(&Gpio, RST_DAC_PIN, 0x0);
gpio_set_value(rst_dac.gpio, value);
#endif

}

void reset_dac(void)
{
put_rst_dac(0x0);
udelay(20);
put_rst_dac(0x1);
}
void init_dac(void)
{
u16 tst;
reset_dac();
wr_dat_fpga(ADDR_SPI_CS_A,0x1);///ncs =1
////wr_spi_dat(ADDR_CONFIG2,0x7f<<7);	///lvdsdata ena
mod_get_spi_da(ADDR_CONFIG1,&tst);
///tst |= iotest_ena_bit;
tst &= ~fullwordinterface_ena_bit;
mod_put_spi_da(ADDR_CONFIG1,tst);	///lvdsdata ena
}



///====================================
long sparrow_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
int retval = 0;
int tmp;
if( ( _IOC_TYPE( cmd ) != IOC_MAGIC ) )
	return -ENOTTY;
////printk( KERN_INFO "\n=== spark_trk_ioctl : %x\n" ,cmd);  //

switch( cmd )
	{
	case IOCTL_SET_SPD_SPI_ADDA:
		if( copy_from_user(&tmp,  (void*)arg, _IOC_SIZE( cmd ) ) )
			return -EFAULT;
		set_spd_spi_adda(tmp);
		break;
	case IOCTL_PUT_SPI_DA:
		{
		dac_spi_req_t t_dac_spi_req;
		if( copy_from_user(&t_dac_spi_req,  (void*)arg, _IOC_SIZE( cmd ) ) )
			return -EFAULT;
		retval=mod_put_spi_da(t_dac_spi_req.addr,t_dac_spi_req.data);
		}
		break;
///====
	case IOCTL_SET_SPI_DA_REQ:
		{
		dac_spi_req_t t_dac_spi_req;
////	printk( KERN_ERR "\n=== mod_IOCTL_SET_XIL_REQ " );  //
		if( copy_from_user(&t_dac_spi_req, (void*)arg,  _IOC_SIZE( cmd ) ) )
			{
////			printk( KERN_INFO "error : %d\n" ,-EFAULT);  //
			return -EFAULT;
			}
		else
			{
			memcpy(&dac_spi_dat_req,&t_dac_spi_req,sizeof(dac_spi_req_t));
	////		printk( KERN_ERR "ok [%x:%x:%x]\n" ,xil_dat_req.addr
	////				,xil_dat_req.ndata,xil_dat_req.data[0] );  //
			}
		}
		break;
	case IOCTL_GET_SPI_DA_DATA:
		{
		dac_spi_req_t t_dac_spi_req;
////		printk( KERN_ERR "\nmod_IOCTL_GET_ALT_DATA ");  //
		get_spi_da_data(&t_dac_spi_req);
		if( copy_to_user( (void*)arg, &t_dac_spi_req, _IOC_SIZE( cmd ) ) )
			{
////			printk( KERN_INFO "error : %d\n" ,-EFAULT);  //
			return -EFAULT;
			}
///		printk( KERN_ERR "ok [%x:%x:%x]\n" ,t_xil_dat_req.addr
///			,t_xil_dat_req.ndata ,t_xil_dat_req.data[0]);  //
		}
		break;
	case IOCTL_INIT_DA:
		if( copy_from_user(&tmp, (void*)arg,  _IOC_SIZE( cmd ) ) )
			{
////			printk( KERN_INFO "error : %d\n" ,-EFAULT);  //
			return -EFAULT;
			}
		else
			{
			init_dac();
	////		printk( KERN_ERR "ok [%x:%x:%x]\n" ,xil_dat_req.addr
	////				,xil_dat_req.ndata,xil_dat_req.data[0] );  //
			}
		break;
///====
	case IOCTL_SET_XIL_REQ:
		{
		xil_dat_req_t t_xil_dat_req;
////	printk( KERN_ERR "\n=== mod_IOCTL_SET_XIL_REQ " );  //

		if( copy_from_user(&t_xil_dat_req, (void*)arg,  _IOC_SIZE( cmd ) ) )
			{
////			printk( KERN_INFO "error : %d\n" ,-EFAULT);  //
			return -EFAULT;
			}
		else
			{
			memcpy(&xil_dat_req,&t_xil_dat_req,sizeof(xil_dat_req_t));
	////		printk( KERN_ERR "ok [%x:%x:%x]\n" ,xil_dat_req.addr
	////				,xil_dat_req.ndata,xil_dat_req.data[0] );  //
			}
		}
		break;
	case IOCTL_GET_XIL_DATA:
		{
			xil_dat_req_t t_xil_dat_req;
////		printk( KERN_ERR "\nmod_IOCTL_GET_ALT_DATA ");  //

////		get_alt_data(&t_alt_dat_req);
		get_xil_data(&t_xil_dat_req);
		if( copy_to_user( (void*)arg, &t_xil_dat_req, _IOC_SIZE( cmd ) ) )
			{
////			printk( KERN_INFO "error : %d\n" ,-EFAULT);  //
			return -EFAULT;
			}
///		printk( KERN_ERR "ok [%x:%x:%x]\n" ,t_xil_dat_req.addr
///			,t_xil_dat_req.ndata ,t_xil_dat_req.data[0]);  //
		}
		break;
	case IOCTL_SET_XIL_DATA:
		{
		xil_dat_req_t t_xil_data;
		if( copy_from_user(&t_xil_data, (void*)arg,  _IOC_SIZE( cmd ) ) )
			{
			return -EFAULT;
			}
		else
			{
///			put_alt_data(&t_alt_data);
			put_xil_data(&t_xil_data);
///			printk( KERN_ERR "\n IOCTL_SET_XIL_DATA [%x:%x:%x]\n" ,t_xil_data.addr
///				,t_xil_data.ndata ,t_xil_data.data[0]);  //

			}
		}
		break;
	   case IOCTL_GET_VERS:
	     if( copy_to_user( (void*)arg, vers_str, _IOC_SIZE( cmd ) ) )
	   	  return -EFAULT;
	      break;
   default:
      return -ENOTTY;
}
return retval;
}
///+++++++++++++++++++++++++++++++++++
///+++++++++++++++++++++++++++++++++++
