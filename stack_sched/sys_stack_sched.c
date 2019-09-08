#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/moduleloader.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/delay.h>
#include "dummy_struct.h"

asmlinkage extern long (*sysptr_stack_sched)(void *arg);

asmlinkage long stack_sched(void *arg)
{
	unsigned long *addr;

	addr = (unsigned long *)current->stack;
	pr_info("Current stack %p\n", current->stack);
	pr_info("address of the pointer %p\n", addr);
	pr_info("Current stack value %lu\n", *(addr));
	/*updating the stack value for the current of type task_struct*/
	*(addr) = *(addr) + 30;
	pr_info("Current stack value %lu\n", *(addr));
	return 0;
}
static int __init init_sys_stack_sched(void)
{
	pr_info("installed stack_sched module!\n");
	if (!sysptr_stack_sched)
		sysptr_stack_sched = stack_sched;
	return 0;
}

static void __exit exit_sys_stack_sched(void)
{
	if (sysptr_stack_sched)
		sysptr_stack_sched = NULL;
	pr_info("removed stack_sched module!\n");
}

module_init(init_sys_stack_sched);
module_exit(exit_sys_stack_sched);
MODULE_LICENSE("GPL");
