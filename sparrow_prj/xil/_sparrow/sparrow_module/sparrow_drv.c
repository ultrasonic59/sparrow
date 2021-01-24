/*
 */

#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/cdev.h>

#include <linux/bitops.h>
#include <linux/init.h>
#include <linux/errno.h>
#include <linux/module.h>

#include <linux/of_device.h>
#include <linux/of_irq.h>
#include <linux/of_address.h>
#include <linux/of_platform.h>
#include <linux/of_gpio.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/irq.h>
#include <linux/irqchip/chained_irq.h>
#include <linux/irqdomain.h>
#include <linux/gpio.h>
#include <linux/slab.h>
#include <linux/kdev_t.h>
#include "sparrow_drv.h"
#include "../common_inc/sparrow_types.h"
///#include "sepia_mod_type.h"


///=====================================================
#define VERS "1.1.1"

#define SPARROW	(0x43C00000)
#define SPARROW_NR	0x10000
#define IRQ_NUM		45	///61

///unsigned long sparrow_trk_base = 0x43C00000;	////????
unsigned long sparrow_base = SPARROW;	////????

static int major = 0;
module_param( major, int, S_IRUGO );
#define DEVICE_FIRST  0
#define DEVICE_COUNT  1

MODULE_AUTHOR( "Vladimir A. Golev" );
MODULE_VERSION( VERS );
#define MODNAME "sparrow"
static struct cdev hcdev;
char vers_str[160];

static int sparrow_open(struct inode *inodep,struct file *filp);

static const struct file_operations dev_fops = {
   .owner = THIS_MODULE,
   .open = sparrow_open,
   .read  = sparrow_read,
   .write  = sparrow_write,
   .unlocked_ioctl = sparrow_ioctl,
   .llseek =sparrow_lseek,
};
///========================================================
struct gpio rst_dac;
int ready_dat;
extern u8 g_req_osc;
extern u8 on_off_izl;
extern void clr_ext_irq(void);
///extern void mod_get_amps_tims(void);
extern u8 *mod_buffOscs;
extern void psk_izm(int idat);

///[NUM_OSC][MAX_OSC_LEN];
#if 0
static irqreturn_t ext_interrupt(int irq, void *dev_id)
{
clr_ext_irq( );
////printk( KERN_ERR "\n=== [mod]ext_trk_interrupt");
#if 0
if(on_off_izl)
	{
	psk_izm(0x1);
////	t_tst++;
///mod_put_ex_led(t_tst>>6);

///	mod_get_amps_tims();
	mod_get_zamer();
	if(g_req_osc)
		{
		mod_get_osc();
////		printk(KERN_ERR "[mod]>");
		g_req_osc=0;
		}
	ready_dat=1;
////	mod_put_led(0xf);
////	start_timer_for_trk();
	}
#endif
return IRQ_HANDLED;
}
#endif

static int sparrow_open(struct inode *inodep,struct file *filp)
{
#if 0
int err = 0;
///err = request_irq(IRQ_EINT(0), ext_trk_interrupt, IRQ_TYPE_EDGE_RISING,
err = request_irq(61, ext_trk_interrupt, 0,
"Ext Trk Irq", NULL);
 if (err)
 	 {
	 printk(KERN_ERR "\n[mod]request_irq error[%d]\n",err);
     return -EBUSY;
 	 }
////int retval = 1;
///int tmp;
#endif
printk(KERN_ERR "\n[mod]sparrow_open\n");
///	mod_set_ug_conf(0);			///disable irq trk

return 0;
}
///====================================================================================
#if 1

////int g_irq;

///=====================================================
static int udef_of_probe(struct platform_device *pdev)
{
struct device_node *np = pdev->dev.of_node;
int ret;
////int tst_dat=0;
int rc = 0;
dev_t dev;
///int irq;
struct resource res;
void *registers;
int rez=0;
rc = of_address_to_resource(np, 0, &res);

if (rc) {
/* Fail */
	printk(KERN_ALERT"==>Fail ==\n");
  }

if  (!request_mem_region(res.start, resource_size(&res), "udef"))
	{
    /* Fail */
	printk(KERN_ALERT"request_mem_region ==>Fail ==\n");
	}
///printk(KERN_ALERT"\n ==== of_iomap =====");
registers = of_iomap(np, 0);
if (!registers)
	{
	    /* Fail */
	printk(KERN_ALERT"==>Fail ==\n");
	}
#if 0
////printk(KERN_ALERT"===>OK[%x]==\n",(int)registers);
////printk(KERN_ALERT"\n ==== irq_of_parse_and_map =====");
g_irq = irq_of_parse_and_map(np, 0);
///printk(KERN_ALERT"===>OK[%x]==\n",(int)g_irq);
////printk(KERN_ALERT"\n ==== request_irq =====");

////rc = request_irq(irq, ext_trk_interrupt, 0, "udef", op->dev);
rc = request_irq(g_irq, ext_interrupt, 0, "udef", NULL);
if (rc)
	 {
	 printk(KERN_ERR "\n[mod]request_irq error[%d]\n",rc);
    return -EBUSY;
	 }
#endif
////printk(KERN_ERR "\n[mod]request_irq ok\n");
///tst_dat=ioread16(registers+0x400a);
///printk(KERN_ALERT"/n ===tst_dat[%x]==\n",tst_dat);
///pr_err("==============octopuz_trk_mod===============\r\n");
/////printk(KERN_ALERT "cdev_octopuz_trk_mod init \n");
///printk(KERN_ALERT " cdev_init \n");

if( major != 0 )
	{
	dev = MKDEV( major, DEVICE_FIRST );
	rez = register_chrdev_region( dev, DEVICE_COUNT, MODNAME );
	}
else
	{
	rez = alloc_chrdev_region( &dev, DEVICE_FIRST, DEVICE_COUNT, MODNAME );
	major = MAJOR( dev );  	/// не забыть зафиксировать!
	}
if( rez < 0 )
	{
	printk( KERN_ALERT "=== Can not register char device region\n" );
	goto err;
	}
///printk(KERN_INFO "cdev_init1\n");
cdev_init( &hcdev, &dev_fops );
hcdev.owner = THIS_MODULE;
///printk(KERN_ALERT "cdev_add\n");
rez = cdev_add( &hcdev, dev, DEVICE_COUNT );
if( rez < 0 )
	{
	unregister_chrdev_region( MKDEV( major, DEVICE_FIRST ), DEVICE_COUNT );
	printk( KERN_ALERT "=== Can not add char device\n" );
	goto err;
	}
///bl_init_def_par(&mod_curr_param);
////	octopuz_trk_base=OCTOPUZ_TRK;
sparrow_base=(unsigned long)registers;
	///printk(KERN_ALERT "octopuz_trk_mod=[0x%lx]\n",octopuz_trk_base);
	memset(vers_str,0,160);
	////printk(KERN_ALERT "octopuz_trk_mod1=[0x%lx]\n",octopuz_trk_base);
	sprintf(vers_str,"[v%s][%s][%s]",VERS,__DATE__,__TIME__);
///				printk(KERN_INFO "weasel_trk_mod=[0x%lx][%s][%s]\n",weasel_trk_base,__DATE__,__TIME__);
	printk(KERN_ALERT "sparrow_mod=[0x%lx]%s\n",sparrow_base,vers_str);
///========================================================================
	   if (!gpio_is_valid(RST_DAC_PIN))
	    {
	        printk(KERN_ALERT " GPIO number %d not valid.\n", RST_DAC_PIN);
////	        return 1;
	    }
	   else
	   {
////	     printk(KERN_ALERT " GPIO number %d ok.\n", RST_DAC_PIN);
    ret = gpio_request(RST_DAC_PIN,"DAC_RST");
    if (ret)
    {
        printk(KERN_ALERT "Gpio request failed.\n");
////        return -2;
    }
    else
    	{
    	rst_dac.gpio=RST_DAC_PIN;
    	rst_dac.label = "DAC_RST";
        gpio_direction_output(rst_dac.gpio, 0);
        gpio_set_value(rst_dac.gpio, 1);

        printk(KERN_ALERT "Gpio request ok\n");

    	}
	   }
///========================================================================
	///++++++++++++++++++++++++++++++++++++++++++
#if 0
///	t_par_buff = kmalloc(sizeof(par_contr_t)+8, GFP_KERNEL);
///	t_par_buff = kmalloc(sizeof(par_trk_t)+sizeof(ed_par_trk_t)+4, GFP_KERNEL);
	t_par_buff = kmalloc(sizeof(par_device_t)+4, GFP_KERNEL);
	if (!t_par_buff)
		{
		printk(KERN_ERR "\n[mod]Error t_par_buff no Mem!!!");
		rez = -ENOMEM;
		goto err;  /* Make this more graceful */
		}
#endif
#if 0
////	mod_buffOscs = kmalloc(NUM_OSC*MAX_OSC_LEN+8, GFP_KERNEL);
	mod_buffOscs = kmalloc(600, GFP_KERNEL);
	if (!mod_buffOscs)
		{
		printk(KERN_ERR "\n[mod]Error mod_buffOscs no Mem!!!");
		rez = -ENOMEM;
		goto err;  /* Make this more graceful */
		}
#endif
///	printk(KERN_ALERT "\n ====init_mod_rez_rb==== \n");
////	init_mod_rez_rb(LEN_MOD_RING_REZ);
///	printk(KERN_ERR "\n[mod]mod_set_ug_conf");
///	mod_set_ug_conf(0);			///disable irq trk

err:
	return rez;
}
///===============================================================
static const struct of_device_id udef_of_match[] = {
	{ .compatible = "vlg,axi-udef-1.0", },
	{ /* end of list */ },
};
MODULE_DEVICE_TABLE(of, udef_of_match);

static struct platform_driver sparrow_driver = {
	.probe = udef_of_probe,
	.driver = {
		.name = "udef",
		.of_match_table = udef_of_match,
	},
};
#endif
#if 1
static int __init sparrow_init(void)
{
int rez=0;
///pr_err("==============octopuz_trk===============\r\n");
////printk(KERN_ERR "\r\n===================sepia_trk_init========================");
rez=platform_driver_register(&sparrow_driver);
///printk(KERN_ALERT "platform_driver_register[%d]\r\n",rez);
return rez;
}

static void sparrow_exit(void)
{
///devm_kfree(&pdev->dev);
platform_driver_unregister(&sparrow_driver);
////free_irq(g_irq, &ext_interrupt);

printk(KERN_ALERT "Goodbye, sparrow\n");
}
#endif


///====================================================================================
module_init(sparrow_init);
module_exit(sparrow_exit);
MODULE_AUTHOR("Velog, Ltd.");
MODULE_DESCRIPTION("Velog ADC&DAC driver");
MODULE_LICENSE("GPL");
