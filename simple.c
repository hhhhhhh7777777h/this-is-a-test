/**
 * simple.c
 *
 * A simple kernel module. 
 * 
 * To compile, run makefile by entering "make"
 *
 * Operating System Concepts - 10th Edition
 * Copyright John Wiley & Sons - 2018
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/hash.h>
#include <linux/gcd.h>
#include <linux/jiffies.h>
#include <asm/param.h>

/* This function is called when the module is loaded. */
static int simple_init(void)
{
    printk(KERN_INFO "Loading Module\n");

    printk(KERN_INFO "golden: %lu\n", GOLDEN_RATIO_PRIME);

    printk(KERN_INFO "hz: %d\n", HZ);
    printk(KERN_INFO "jiffies: %lu\n", jiffies);

    return 0;
}

/* This function is called when the module is removed. */
static void simple_exit(void)
{
    printk(KERN_INFO "Removing Module\n");

    printk(KERN_INFO "gcd: %lu\n", gcd(3300, 24));

    // Print jiffies at exit
    printk(KERN_INFO "jiffies: %lu\n", jiffies);

}

/* Macros for registering module entry and exit points. */
module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Kernel Module");
MODULE_AUTHOR("SGG");
