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
	{ 0x3c40101, "__platform_driver_register" },
	{ 0x2303550f, "device_property_present" },
	{ 0x336c7170, "device_property_read_string" },
	{ 0x4d03c274, "device_property_read_u32_array" },
	{ 0x8da6585d, "__stack_chk_fail" },
	{ 0x8cfd0a21, "platform_driver_unregister" },
	{ 0xf429ccb8, "module_layout" },
};

MODULE_INFO(depends, "");

MODULE_ALIAS("of:N*T*Cbrightlight,mydev");
MODULE_ALIAS("of:N*T*Cbrightlight,mydevC*");

MODULE_INFO(srcversion, "7582B824E24F50F1D987B7B");
