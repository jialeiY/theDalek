#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif


static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x92997ed8, "_printk" },
	{ 0x6cbbfc54, "__arch_copy_to_user" },
	{ 0xa73bbee3, "__register_chrdev" },
	{ 0x47229b5c, "gpio_request" },
	{ 0x860778f5, "gpio_to_desc" },
	{ 0x42fbc5e2, "gpiod_direction_output_raw" },
	{ 0xfe990052, "gpio_free" },
	{ 0x4a62cb8e, "gpiod_set_raw_value" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0xf429ccb8, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "BFB3D510EBB005F93AA312B");
