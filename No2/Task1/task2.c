#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Akshat Sinha");
MODULE_DESCRIPTION("A simple example Linux module.");
MODULE_VERSION("0.01");

extern int a1;  // Global variable 'a1' declared

// Exporting symbol 'a1' so it can be used by other modules


// Module initialization function
static int __init hello_init(void)
{
    printk(KERN_INFO "Gia tri cua a la: %d", a1);
      // Assigning a value to global variable 'a1'
    return 0; // Indicating success
}

// Module cleanup function
static void __exit hello_exit(void)
{
    printk(KERN_INFO "Goodbye world\n");
}

// Registering the initialization and cleanup functions
module_init(hello_init);
module_exit(hello_exit);
