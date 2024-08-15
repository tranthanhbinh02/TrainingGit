#include <linux/module.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/of_gpio.h>
#include <linux/gpio.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "sample_led"
#define CLASS_NAME  "led"
#define LED_PIN 53

static int major;
static struct class*  ledClass  = NULL;
static struct device* ledDevice = NULL;
static int led_gpio;

static ssize_t led_write(struct file *file, const char *buffer, size_t len, loff_t *offset) {
    char msg;
    if (copy_from_user(&msg, buffer, 1)) return -EFAULT;
    if (msg == '1') gpio_set_value(led_gpio, 1);
    else if (msg == '0') gpio_set_value(led_gpio, 0);
    return len;
}

static ssize_t led_read(struct file *file, char *buffer, size_t len, loff_t *offset) {
    int led_val = gpio_get_value(led_gpio);
    char result = led_val ? '1' : '0';
    if (copy_to_user(buffer, &result, 1)) return -EFAULT;
    return 1;
}

static struct file_operations fops = {
    .write = led_write,
    .read = led_read,
};

static int __init led_init(void) {
    struct device_node *node = of_find_node_by_name(NULL, "led0");
    if (!node) return -ENODEV;
    
    led_gpio = of_get_named_gpio(node, "gpios", 0);
    if (led_gpio < 0) return led_gpio;
    
    gpio_request(led_gpio, "LED_GPIO");
    gpio_direction_output(led_gpio, 0);
    
    major = register_chrdev(0, DEVICE_NAME, &fops);
    ledClass = class_create(THIS_MODULE, CLASS_NAME);
    ledDevice = device_create(ledClass, NULL, MKDEV(major, 0), NULL, DEVICE_NAME);
    
    return 0;
}

static void __exit led_exit(void) {
    gpio_set_value(led_gpio, 0);
    gpio_free(led_gpio);
    device_destroy(ledClass, MKDEV(major, 0));
    class_unregister(ledClass);
    class_destroy(ledClass);
    unregister_chrdev(major, DEVICE_NAME);
}

module_init(led_init);
module_exit(led_exit);

MODULE_LICENSE("GPL");

