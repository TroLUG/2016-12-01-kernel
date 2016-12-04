#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>

static dev_t mydev;
static char output[] = "Hallo Trolug";
struct cdev my_cdev;
static int opened = 0;

ssize_t lesen(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
	if(output[*f_pos] == '\0')
		return 0;
	copy_to_user(buf, &output[*f_pos],1);
	*f_pos += 1;
	return 1;
}
ssize_t oeffnen(struct inode *inodep, struct file *filep)
{
	printk(KERN_INFO "Die Datei wurde schon %d mal geoeffnet", ++opened);
	return 0;
}
ssize_t loesen(struct inode *inodep, struct file *filep)
{
	printk(KERN_INFO "Fertig!");
	return 0;
}
ssize_t schreiben(struct file *filp, const char *buf, size_t len, loff_t * offset)
{
	printk(KERN_INFO "Der empfangene Text: %s", buf);
	return len;
}
struct file_operations my_fops = {
	.owner = THIS_MODULE,
	.open = oeffnen,
	.read = lesen,
	.write = schreiben,
	.release = loesen,
};
static char buffer[64];
static int __init foo(void)
{
	printk(KERN_INFO "testdriver wurde geladen");
	alloc_chrdev_region(&mydev,0,1,"testdriver");
	printk(KERN_INFO "%s\n", format_dev_t(buffer,mydev));
	cdev_init(&my_cdev, &my_fops);
	my_cdev.owner = THIS_MODULE;
	cdev_add(&my_cdev, mydev, 1);
	return 0;
}
static void __exit bar(void)
{
	printk(KERN_INFO "Das Modul wurde beendet!");
	cdev_del(&my_cdev);
	unregister_chrdev_region(mydev, 1);
}
module_init(foo);
module_exit(bar);
