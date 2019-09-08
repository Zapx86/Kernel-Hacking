#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/moduleloader.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/delay.h>
#include <linux/kthread.h>
#include <linux/device.h>
#include <linux/dma-mapping.h>

#include "dummy_struct.h"
static void dev_release(struct device *dev);

static struct device new_device = {
	.release = dev_release
};

static void dev_release(struct device *dev)
{
	device_unregister(&new_device);
	pr_info("DMA device is released\n");
}

asmlinkage extern long (*sysptr_dmadevice)(void *arg);
asmlinkage long dmadevice(void *arg)
{
	static dma_addr_t dev_handle;
	char *dev_buffer;
	int dir = DMA_BIDIRECTIONAL;
	size_t size = 4096;

	dev_set_name(&new_device, "mydevice");
	device_register(&new_device);

	dev_buffer = kmalloc(size, GFP_KERNEL);
	dev_handle = dma_map_single(&new_device, dev_buffer, size, dir);
	dma_unmap_single(&new_device, dev_handle, size, dir);

	kfree(dev_buffer);
	new_device.release;

	return 0;
}

static int __init init_sys_dmadevice(void)
{
	pr_info("installed dma device module!\n");
	if (!sysptr_dmadevice)
		sysptr_dmadevice = dmadevice;

	return 0;
}

static void __exit exit_sys_dmadevice(void)
{
	if (sysptr_dmadevice)
		sysptr_dmadevice = NULL;
	pr_info("removed dma device module!\n");
}

module_init(init_sys_dmadevice);
module_exit(exit_sys_dmadevice);
MODULE_LICENSE("GPL");
