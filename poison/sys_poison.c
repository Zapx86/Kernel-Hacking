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

asmlinkage extern long (*sysptr_poison)(void *arg);

asmlinkage long poison(void *arg)
{
	DUMMY_STRUCT *k_arg;
	const char src[50] = "checking the data corruption";
	char *dest = kmalloc(50, GFP_KERNEL);
	int option = 0;

	memcpy(dest, src, strlen(src) + 1);
	kfree(dest);

	k_arg = kmalloc(sizeof(DUMMY_STRUCT), GFP_KERNEL);

	if (!k_arg)
		return -ENOMEM;

	if (copy_from_user(k_arg, arg, sizeof(DUMMY_STRUCT))) {
		kfree(k_arg);
		return -EFAULT;
	}

	option = k_arg->val;
	switch (option) {
	case 1:
		pr_info("Double freeing");
		kfree(dest);
		break;
	case 2:
		pr_info("Use after free bug Poisson overwritten");
		memcpy(dest, src, strlen(src) + 1);
		break;
	}

	kfree(k_arg);
	return 0;
}
static int __init init_sys_poison(void)
{
	pr_info("installed poison module!\n");
	if (!sysptr_poison)
		sysptr_poison = poison;
	return 0;
}

static void __exit exit_sys_poison(void)
{
	if (sysptr_poison)
		sysptr_poison = NULL;
	pr_info("removed poison module!\n");
}

module_init(init_sys_poison);
module_exit(exit_sys_poison);
MODULE_LICENSE("GPL");
