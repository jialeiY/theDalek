/***************************************************************************/ /**
                                                                               *  \file       driver.c
                                                                               *
                                                                               *  \details    Simple Linux device driver (Kernel Timer)
                                                                               *
                                                                               *  \author     EmbeTronicX
                                                                               *
                                                                               *  \Tested with Linux raspberrypi 5.10.27-v7l-embetronicx-custom+
                                                                               *
                                                                               *******************************************************************************/
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/timer.h>
#include <linux/jiffies.h>
#include <linux/err.h>
#include <linux/gpio.h>
#include <linux/gpio/consumer.h>
// Timer Variable
#define TIMEOUT 1000 // milliseconds

static struct timer_list etx_timer;
static unsigned int count = 0;
static int gs = 0;

dev_t dev = 0;
static struct class *dev_class;
static struct cdev etx_cdev;

static int __init etx_driver_init(void);
static void __exit etx_driver_exit(void);

/*************** Driver functions **********************/
static int etx_open(struct inode *inode, struct file *file);
static int etx_release(struct inode *inode, struct file *file);
static ssize_t etx_read(struct file *filp, char __user *buf, size_t len, loff_t *off);
static ssize_t etx_write(struct file *filp, const char *buf, size_t len, loff_t *off);
/******************************************************/

unsigned long jiff = 0;

// File operation structure
static struct file_operations fops =
    {
        .owner = THIS_MODULE,
        .read = etx_read,
        .write = etx_write,
        .open = etx_open,
        .release = etx_release,
};

// Timer Callback function. This will be called when timer expires
void timer_callback(struct timer_list *data)
{
    /* do your timer stuff here */
    // pr_info("Timer Callback function Called [%d], jf:[%ld], sysjif: [%ld]\n", count++, jiff, jiffies);

    gs = 1 - gs;
    gpio_set_value(16, 1);
    gpio_set_value(16, 0);
    // gpio_set_value(16, gs);

    /*
       Re-enable timer. Because this function will be called only first time.
       If we re-enable this will work like periodic timer.
    */
    // mod_timer(&etx_timer, jiffies + msecs_to_jiffies(TIMEOUT));
    mod_timer(&etx_timer, jiffies + jiff);
}

/*
** This function will be called when we open the Device file
*/
static int etx_open(struct inode *inode, struct file *file)
{
    pr_info("Device File Opened...!!!\n");
    return 0;
}

/*
** This function will be called when we close the Device file
*/
static int etx_release(struct inode *inode, struct file *file)
{
    pr_info("Device File Closed...!!!\n");
    return 0;
}

/*
** This function will be called when we read the Device file
*/
static ssize_t etx_read(struct file *filp,
                        char __user *buf, size_t len, loff_t *off)
{
    pr_info("Read Function\n");
    return 0;
}

/*
** This function will be called when we write the Device file
*/
static ssize_t etx_write(struct file *filp,
                         const char __user *buf, size_t len, loff_t *off)
{
    pr_info("Write function\n");
    return len;
}

/*
** Module Init function
*/
static int __init etx_driver_init(void)
{
    int gpio_err = 0;

    /*Allocating Major number*/
    if ((alloc_chrdev_region(&dev, 0, 1, "etx_Dev")) < 0)
    {
        pr_err("Cannot allocate major number\n");
        return -1;
    }
    pr_info("Major = %d Minor = %d \n", MAJOR(dev), MINOR(dev));

    /*Creating cdev structure*/
    cdev_init(&etx_cdev, &fops);

    /*Adding character device to the system*/
    if ((cdev_add(&etx_cdev, dev, 1)) < 0)
    {
        pr_err("Cannot add the device to the system\n");
        goto r_class;
    }

    /*Creating struct class*/
    if (IS_ERR(dev_class = class_create(THIS_MODULE, "etx_class")))
    {
        pr_err("Cannot create the struct class\n");
        goto r_class;
    }

    /*Creating device*/
    if (IS_ERR(device_create(dev_class, NULL, dev, NULL, "etx_device")))
    {
        pr_err("Cannot create the Device 1\n");
        goto r_device;
    }

    /* setup your timer to call my_timer_callback */
    // If you face some issues and using older kernel version, then you can try setup_timer API(Change Callback function's argument to unsingned long instead of struct timer_list *.
    timer_setup(&etx_timer, timer_callback, 0);

    /* setup timer interval to based on TIMEOUT Macro */
    jiff = msecs_to_jiffies(TIMEOUT);
    jiff = 0;
    mod_timer(&etx_timer, jiffies + jiff);

    // Setup GPIO
    gpio_err = gpio_request(16, "Cooboc");
    if (gpio_err != 0)
    {
        printk("GPIO request failed");
    }
    // Set output
    gpio_err = gpio_direction_output(16, 1);
    if (gpio_err != 0)
    {
        printk("Setting GPIO direction failed");
        gpio_free(16);
    }
    // Set default value;
    gpio_set_value(16, 0);

    pr_info("Device Driver Insert...Done!!!\n");
    return 0;
r_device:
    class_destroy(dev_class);
r_class:
    unregister_chrdev_region(dev, 1);
    return -1;
}

/*
** Module exit function
*/
static void __exit etx_driver_exit(void)
{
    /* remove kernel timer when unloading module */
    del_timer(&etx_timer);
    device_destroy(dev_class, dev);
    class_destroy(dev_class);
    cdev_del(&etx_cdev);
    unregister_chrdev_region(dev, 1);
    // release GPIO
    gpio_free(16);
    pr_info("Device Driver Remove...Done!!!\n");
}

module_init(etx_driver_init);
module_exit(etx_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("HEQichen <heqichen@gmail.com>");
MODULE_DESCRIPTION("A simple device driver - Kernel Timer");
MODULE_VERSION("1.21");
