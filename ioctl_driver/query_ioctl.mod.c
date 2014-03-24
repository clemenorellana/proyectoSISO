#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xeefda015, "module_layout" },
	{ 0x685f1e51, "device_destroy" },
	{ 0xb0f1af09, "class_destroy" },
	{ 0x324df1ce, "device_create" },
	{ 0x7485e15e, "unregister_chrdev_region" },
	{ 0x55781403, "cdev_del" },
	{ 0x15645a4d, "__class_create" },
	{ 0x1ce031f9, "cdev_add" },
	{ 0x92f24486, "cdev_init" },
	{ 0x29537c9e, "alloc_chrdev_region" },
	{ 0x2f287f0d, "copy_to_user" },
	{ 0x362ef408, "_copy_from_user" },
	{ 0xb4390f9a, "mcount" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "7B3702ECD3AAA285F355D4E");
