#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/moduleloader.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/atomic.h>
#include <linux/spinlock.h>
#include <linux/delay.h>
#include <linux/atomic.h>
#include <linux/kthread.h>
#include "dummy_struct.h"

asmlinkage extern long (*sysptr_hung)(void *arg);

asmlinkage long hung(void *arg)
{
	msleep(20000);
	/*I'm creating the bug by letting the task_struct to sleep > 5sec*/
	return 0;
}
static int __init init_sys_hung(void)
{
	pr_info("installed hung module!\n");
	if (!sysptr_hung)
		sysptr_hung = hung;
	return 0;
}

static void __exit exit_sys_hung(void)
{
	if (sysptr_hung)
		sysptr_hung = NULL;
	pr_info("removed hung module!\n");
}

module_init(init_sys_hung);
module_exit(exit_sys_hung);
MODULE_LICENSE("GPL");
