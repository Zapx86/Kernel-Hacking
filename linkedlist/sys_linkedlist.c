#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/moduleloader.h>
#include <linux/list.h>
#include <linux/slab.h>
#include "dummy_struct.h"

asmlinkage extern long (*sysptr_linkedlist)(void *arg);

struct val_list {
	struct list_head list;
	int val;
} VAL_LIST;

int corrupted_linkedlist(void)
{
	int ret = 0;
	struct list_head head;
	struct val_list *one;

	one = kmalloc(sizeof(struct val_list *), GFP_KERNEL);
	one->val = 1;
	INIT_LIST_HEAD(&head);
	list_add(&one->list, &head);
	list_del(&one->list);
	list_del(&one->list);
	kfree(one);
	return ret;
}

asmlinkage long linkedlist(void *arg)
{
	int ret = 0;

	pr_info("Inside linkedlist_module\n");
	ret = corrupted_linkedlist();
	return ret;
}

static int __init init_sys_linkedlist(void)
{
	pr_info("installed linkedlist module!\n");
	if (!sysptr_linkedlist)
		sysptr_linkedlist = linkedlist;
	return 0;
}

static void __exit exit_sys_linkedlist(void)
{
	if (sysptr_linkedlist)
		sysptr_linkedlist = NULL;
	pr_info("removed linkedlist module!\n");
}

module_init(init_sys_linkedlist);
module_exit(exit_sys_linkedlist);
MODULE_LICENSE("GPL");
