#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/jiffies.h>
#include <asm/param.h>
#include <linux/uaccess.h>

#define BUFFER_SIZE 128
#define PROC_JIFFIES "jiffies"
#define PROC_SECONDS "seconds"

static unsigned long start_jiffies;

static ssize_t jiffies_read(struct file *file, char __user *usr_buf, size_t count, loff_t *pos);
static ssize_t seconds_read(struct file *file, char __user *usr_buf, size_t count, loff_t *pos);

static struct file_operations jiffies_fops = {
    .owner = THIS_MODULE,
    .read = jiffies_read,
};

static struct file_operations seconds_fops = {
    .owner = THIS_MODULE,
    .read = seconds_read,
};

static int proc_init(void) {
    start_jiffies = jiffies;
    proc_create(PROC_JIFFIES, 0666, NULL, &jiffies_fops);
    proc_create(PROC_SECONDS, 0666, NULL, &seconds_fops);
    printk(KERN_INFO "/proc/%s and /proc/%s created\n", PROC_JIFFIES, PROC_SECONDS);
    return 0;
}

static void proc_exit(void) {
    remove_proc_entry(PROC_JIFFIES, NULL);
    remove_proc_entry(PROC_SECONDS, NULL);
    printk(KERN_INFO "/proc/%s and /proc/%s removed\n", PROC_JIFFIES, PROC_SECONDS);
}

static ssize_t jiffies_read(struct file *file, char __user *usr_buf, size_t count, loff_t *pos) {
    static int completed = 0;
    char buffer[BUFFER_SIZE];
    int rv;

    if (completed) {
        completed = 0;
        return 0;
    }
    completed = 1;

    rv = sprintf(buffer, "%lu\n", jiffies);
    copy_to_user(usr_buf, buffer, rv);
    return rv;
}

static ssize_t seconds_read(struct file *file, char __user *usr_buf, size_t count, loff_t *pos) {
    static int completed = 0;
    char buffer[BUFFER_SIZE];
    int rv;
    unsigned long elapsed_seconds = (jiffies - start_jiffies) / HZ;

    if (completed) {
        completed = 0;
        return 0;
    }
    completed = 1;

    rv = sprintf(buffer, "%lu\n", elapsed_seconds);
    copy_to_user(usr_buf, buffer, rv);
    return rv;
}

module_init(proc_init);
module_exit(proc_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Proc File System Kernel Module");
MODULE_AUTHOR("SGG");
