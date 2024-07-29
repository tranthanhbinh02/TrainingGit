#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kthread.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Binh");

static int count = 0;
static DEFINE_SPINLOCK(count_spin);

int count_to_billion(void *data) {
    unsigned long i;
    for (i = 1; i <= 500000000; i++) {
        spin_lock(&count_spin);
        count++;
        spin_unlock(&count_spin);
    }
    printk(KERN_INFO "Bo may xong roi\n");
    return 0;
}

static struct task_struct *thread1, *thread2;

static int __init hello_init(void) {
    printk(KERN_INFO "Module initialized\n");

    // Create thread1
    thread1 = kthread_create(count_to_billion, NULL, "thread1");
    if (!thread1) {
        printk(KERN_ERR "Failed to create thread1\n");
        return -ENOMEM;
    }
    wake_up_process(thread1);

    // Create thread2
    thread2 = kthread_create(count_to_billion, NULL, "thread2");
    if (!thread2) {
        printk(KERN_ERR "Failed to create thread2\n");
        kthread_stop(thread1);  // Stop thread1 if thread2 creation fails
        return -ENOMEM;
    }
    wake_up_process(thread2);

    return 0;
}

static void __exit hello_exit(void) {
    printk(KERN_INFO "Count = %d\n", count);
    // kthread_stop(thread1);
    // kthread_stop(thread2);
    
}

module_init(hello_init);
module_exit(hello_exit);
