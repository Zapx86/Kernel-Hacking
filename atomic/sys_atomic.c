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

asmlinkage extern long (*sysptr_atomic)(void *arg);

asmlinkage long atomic(void *arg)
{
	int var = 0;
	int i = 2;
	int *ptr;
	static spinlock_t my_lock = __SPIN_LOCK_UNLOCKED();

	spin_lock(&my_lock);
	var += 1;
	while (i > 0) {
		i--;
		ptr = kmalloc(2000, GFP_KERNEL);
		pr_info("spin lock atomicity corruption %d and pointer %p\n", i
			, ptr);
		kfree(ptr);
	}
	spin_unlock(&my_lock);
	return 0;
}
static int __init init_sys_atomic(void)
{
	pr_info("installed atomic module!\n");
	if (!sysptr_atomic)
		sysptr_atomic = atomic;
	return 0;
}

static void __exit exit_sys_atomic(void)
{
	if (sysptr_atomic)
		sysptr_atomic = NULL;
	pr_info("removed atomic module!\n");
}

module_init(init_sys_atomic);
module_exit(exit_sys_atomic);
MODULE_LICENSE("GPL");
