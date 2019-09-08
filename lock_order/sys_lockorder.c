#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/moduleloader.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/spinlock.h>
#include <linux/delay.h>
#include <linux/kthread.h>

#include "dummy_struct.h"

asmlinkage extern long (*sysptr_livelock)(void *arg);

asmlinkage long livelock(void *arg)
{
	int var = 0;
	static spinlock_t my_lock1 = __SPIN_LOCK_UNLOCKED();

	spin_lock(&my_lock1);
	var += 1;

	return 0;
}

static int __init init_sys_livelock(void)
{
	pr_info("installed livelock module!\n");

	if (!sysptr_livelock)
		sysptr_livelock = livelock;

	return 0;
}

static void __exit exit_sys_livelock(void)
{
	if (sysptr_livelock)
		sysptr_livelock = NULL;
	pr_info("removed livelock module!\n");
}

module_init(init_sys_livelock);
module_exit(exit_sys_livelock);
MODULE_LICENSE("GPL");
