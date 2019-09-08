#include <linux/linkage.h>
#include <linux/moduleloader.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/syscalls.h>
#include <linux/err.h>
#include <linux/scatterlist.h>
#define INVALID_KADDR	(UL(0xC0000000) - UL(0x01))
asmlinkage extern long (*sysptr_sgdebugging)(void *arg);
asmlinkage long sgdebugging(void *arg)
{
	struct scatterlist sg[3];
	void *buffer = (void *)INVALID_KADDR;

	sg_init_table(sg, 3);
	sg_set_buf(&sg[0], buffer, 5);
	return 0;
}

static int __init init_sys_sgdebugging(void)
{
	pr_info("installed new sg debugging module\n");
	if (!sysptr_sgdebugging)
		sysptr_sgdebugging = sgdebugging;
	return 0;
}

static void  __exit exit_sys_sgdebugging(void)
{
	if (sysptr_sgdebugging)
		sysptr_sgdebugging = NULL;
	pr_info("removed sg debugging module\n");
}
module_init(init_sys_sgdebugging);
module_exit(exit_sys_sgdebugging);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Samanvitha Reddy Panyam");
MODULE_DESCRIPTION("SG");
