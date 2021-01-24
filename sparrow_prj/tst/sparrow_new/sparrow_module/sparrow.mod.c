#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xd02fb899, "module_layout" },
	{ 0xae9849dd, "__request_region" },
	{ 0xa6005fff, "cdev_init" },
	{ 0xed2e446, "param_ops_int" },
	{ 0xc94d8e3b, "iomem_resource" },
	{ 0x3fd78f3b, "register_chrdev_region" },
	{ 0x47229b5c, "gpio_request" },
	{ 0x9454fd07, "gpio_to_desc" },
	{ 0x28cc25db, "arm_copy_from_user" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x91715312, "sprintf" },
	{ 0x8dffc35b, "__platform_driver_register" },
	{ 0xf4fa543b, "arm_copy_to_user" },
	{ 0x5f754e5a, "memset" },
	{ 0x7c32d0f0, "printk" },
	{ 0xabbbaac1, "of_iomap" },
	{ 0x7552cb08, "gpiod_direction_output_raw" },
	{ 0x8e865d3c, "arm_delay_ops" },
	{ 0xd3df0c5d, "cdev_add" },
	{ 0xdb7305a1, "__stack_chk_fail" },
	{ 0x9d669763, "memcpy" },
	{ 0xa5dce595, "gpiod_set_raw_value" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0x3d8cf02e, "of_address_to_resource" },
	{ 0x2651d5c2, "platform_driver_unregister" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("of:N*T*Cvlg,axi-udef-1.0");
MODULE_ALIAS("of:N*T*Cvlg,axi-udef-1.0C*");

MODULE_INFO(srcversion, "41EC06AF506BDDCAAD2175C");
