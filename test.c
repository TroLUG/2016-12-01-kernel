#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>

static int foo(void)
{
	printk(KERN_INFO "Hello World");
	return 0;
}

static void bar(void)
{
	printk(KERN_INFO "Module has stopped");
}

module_init(foo);
module_exit(bar);
