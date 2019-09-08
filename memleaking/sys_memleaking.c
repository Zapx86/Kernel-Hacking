#include <linux/linkage.h>
#include <linux/moduleloader.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/syscalls.h>
#include <linux/err.h>
#include <linux/slab.h>

asmlinkage extern long (*sysptr_memleaking)(void *arg);
asmlinkage long memleaking(void *arg)
{
	char *a = NULL;

	a = kmalloc(8, GFP_KERNEL);
	//kfree(a);
	return 0;
}

static int __init init_sys_memleaking(void)
{
	pr_info("installed new memleaking module\n");
	if (!sysptr_memleaking)
		sysptr_memleaking = memleaking;
	return 0;
}

static void  __exit exit_sys_memleaking(void)
{
	if (sysptr_memleaking)
		sysptr_memleaking = NULL;
	pr_info("removed memleaking module\n");
}
module_init(init_sys_memleaking);
module_exit(exit_sys_memleaking);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Samanvitha Reddy Panyam");
MODULE_DESCRIPTION("MEMLEAKING");
