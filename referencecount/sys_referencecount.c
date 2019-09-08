#include <linux/linkage.h>
#include <linux/moduleloader.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/syscalls.h>
#include <linux/err.h>
#include <linux/refcount.h>
#define REFCOUNT_MAX		(UINT_MAX - 1)

asmlinkage extern long (*sysptr_referencecount)(void *arg);
asmlinkage long referencecount(void *arg)
{
	refcount_t over = REFCOUNT_INIT(REFCOUNT_MAX - 1);
	
	refcount_inc(&over);
	refcount_inc(&over);
	return 0;
}

static int __init init_sys_referencecount(void)
{
	pr_info("installed new reference count module\n");
	if (!sysptr_referencecount)
		sysptr_referencecount = referencecount;
	return 0;
}

static void  __exit exit_sys_referencecount(void)
{
	if (sysptr_referencecount)
		sysptr_referencecount = NULL;
	pr_info("removed reference count module\n");
}
module_init(init_sys_referencecount);
module_exit(exit_sys_referencecount);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Samanvitha Reddy Panyam");
MODULE_DESCRIPTION("REFERENCE COUNT");
