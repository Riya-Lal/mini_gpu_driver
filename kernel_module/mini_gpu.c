#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include "mini_gpu.h"

#define DEVICE_NAME "mini_gpu"
#define BUFFER_SIZE 1024

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Riya");
MODULE_DESCRIPTION("A minimal GPU-like kernel module simulation");

static int major;
static char buffer[BUFFER_SIZE];
static int open_count = 0;

static int dev_open(struct inode *inodep, struct file *filep) {
    open_count++;
    printk(KERN_INFO "mini_gpu: Device opened (%d times)\n", open_count);
    return 0;
}

static int dev_release(struct inode *inodep, struct file *filep) {
    printk(KERN_INFO "mini_gpu: Device successfully closed\n");
    return 0;
}

static ssize_t dev_read(struct file *filep, char *user_buf, size_t len, loff_t *offset) {
    int bytes_read = len > BUFFER_SIZE ? BUFFER_SIZE : len;
    if (copy_to_user(user_buf, buffer, bytes_read) != 0) {
        return -EFAULT;
    }
    return bytes_read;
}

static ssize_t dev_write(struct file *filep, const char *user_buf, size_t len, loff_t *offset) {
    int bytes_write = len > BUFFER_SIZE ? BUFFER_SIZE : len;
    if (copy_from_user(buffer, user_buf, bytes_write) != 0) {
        return -EFAULT;
    }
    printk(KERN_INFO "mini_gpu: Received data from user space: %s\n", buffer);
    return bytes_write;
}

static long mini_gpu_ioctl(struct file *file, unsigned int cmd, unsigned long arg) {
    struct gpu_command cmd_data;
    if (copy_from_user(&cmd_data, (struct gpu_command *)arg, sizeof(struct gpu_command))) {
        return -EFAULT;
    }

    switch (cmd) {
        case GPU_IOCTL_DRAW_SHAPE:
            switch (cmd_data.shape) {
                case GPU_SHAPE_RECTANGLE:
                    printk(KERN_INFO "mini_gpu: Drawing RECTANGLE at (%d, %d) size (%d x %d)\n",
                           cmd_data.x, cmd_data.y, cmd_data.width, cmd_data.height);
                    break;
                case GPU_SHAPE_CIRCLE:
                    printk(KERN_INFO "mini_gpu: Drawing CIRCLE at (%d, %d) with diameter %d\n",
                           cmd_data.x, cmd_data.y, cmd_data.width);
                    break;
                case GPU_SHAPE_LINE:
                    printk(KERN_INFO "mini_gpu: Drawing LINE from (%d, %d) to (%d, %d)\n",
                           cmd_data.x, cmd_data.y, cmd_data.width, cmd_data.height);
                    break;
                case GPU_SHAPE_TRIANGLE:
                    printk(KERN_INFO "mini_gpu: Drawing TRIANGLE with base starting at (%d, %d), base = %d, height = %d\n",
                           cmd_data.x, cmd_data.y, cmd_data.width, cmd_data.height);
                    break;
                default:
                    printk(KERN_WARNING "mini_gpu: UNKNOWN shape: %d\n", cmd_data.shape);
            }
            break;
        default:
            return -ENOTTY;
    }
	return 0;
}

static struct file_operations fops = {
    .open = dev_open,
    .release = dev_release,
    .read = dev_read,
    .write = dev_write,
    .unlocked_ioctl = mini_gpu_ioctl,
};

static int __init mini_gpu_init(void) {
    major = register_chrdev(0, DEVICE_NAME, &fops);
    if (major < 0) {
        printk(KERN_ALERT "mini_gpu: Failed to register a major number\n");
        return major;
    }
    printk(KERN_INFO "mini_gpu: Registered with major number %d\n", major);
    return 0;
}

static void __exit mini_gpu_exit(void) {
    unregister_chrdev(major, DEVICE_NAME);
    printk(KERN_INFO "mini_gpu: Unregistered device\n");
}

module_init(mini_gpu_init);
module_exit(mini_gpu_exit);

