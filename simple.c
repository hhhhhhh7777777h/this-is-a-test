#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/hash.h>   // For GOLDEN_RATIO_PRIME
#include <linux/gcd.h>    // For gcd function
#include <linux/jiffies.h> // For jiffies
#include <asm/param.h>    // For HZ

/* This function is called when the module is loaded. */
static int simple_init(void)
{
    printk(KERN_INFO "Loading Module\n");

    // Print GOLDEN_RATIO_PRIME
    printk(KERN_INFO "GOLDEN_RATIO_PRIME: %lu\n", GOLDEN_RATIO_PRIME);

    // Print HZ and jiffies at initialization
    printk(KERN_INFO "HZ (Tick Rate): %d\n", HZ);
    printk(KERN_INFO "Initial jiffies: %lu\n", jiffies);

    return 0;
}

/* This function is called when the module is removed. */
static void simple_exit(void)
{
    printk(KERN_INFO "Removing Module\n");

    // Print gcd of 3300 and 24
    printk(KERN_INFO "GCD of 3300 and 24: %lu\n", gcd(3300, 24));

    // Print jiffies at exit
    printk(KERN_INFO "Final jiffies: %lu\n", jiffies);

    // Calculate elapsed time in seconds
    printk(KERN_INFO "Time elapsed: %lu seconds\n", (jiffies - jiffies) / HZ);
}

/* Macros for registering module entry and exit points. */
module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Kernel Module");
MODULE_AUTHOR("SGG");
