#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/moduleloader.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/delay.h>
#include <linux/kthread.h>
#include <linux/spinlock.h>

#include "dummy_struct.h"

asmlinkage extern long (*sysptr_selfdeadlock)(void *arg);

asmlinkage long selfdeadlock(void *arg)
{
	static spinlock_t my_lock = __SPIN_LOCK_UNLOCKED();
	int var = 0;

	/* https://www.kernel.org/doc/Documentation/locking/spinlocks.txt */
	spin_lock(&my_lock);
	var += 1;
	spin_lock(&my_lock);
	spin_unlock(&my_lock);

	return 0;
}

static int __init init_sys_selfdeadlock(void)
{
	pr_info("installed selfdeadlock module!\n");
	if (!sysptr_selfdeadlock)
		sysptr_selfdeadlock = selfdeadlock;
	return 0;
}

static void __exit exit_sys_selfdeadlock(void)
{
	if (sysptr_selfdeadlock)
		sysptr_selfdeadlock = NULL;
	pr_info("removed selfdeadlock module!\n");
}

module_init(init_sys_selfdeadlock);
module_exit(exit_sys_selfdeadlock);
MODULE_LICENSE("GPL");
