#include <linux/init.h>
#include <linux/delay.h>
#include <linux/kthread.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/moduleloader.h>
#include <linux/timer.h>
#include <linux/sched.h>
#include <linux/time.h>
#include "dummy_struct.h"
asmlinkage extern long (*sysptr_softlockup)(void *arg);

asmlinkage long softlockup(void *arg)
{
	unsigned long j0, j1;
	int delay = 50 * HZ;
	int x;

	j0 = jiffies;
	j1 = j0 + delay;
	while (time_before(jiffies, j1))
		x = 1;
	return 0;
}

static int __init init_sys_softlockup(void)
{
	pr_info("installed softlockup module!\n");
	if (!sysptr_softlockup)
		sysptr_softlockup = softlockup;
	return 0;
}

static void __exit exit_sys_softlockup(void)
{
	if (sysptr_softlockup)
		sysptr_softlockup = NULL;
	pr_info("removed softlockup module!\n");
}

module_init(init_sys_softlockup);
module_exit(exit_sys_softlockup);
MODULE_LICENSE("GPL");
