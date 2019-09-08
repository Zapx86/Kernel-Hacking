#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/moduleloader.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/mutex.h>
#include <linux/delay.h>
#include <linux/mutex.h>
#include <linux/kthread.h>

#include "dummy_struct.h"

asmlinkage extern long (*sysptr_mutex)(void *arg);
static DEFINE_MUTEX(lock_1);
static DEFINE_MUTEX(lock_2);

static int thread_function1(void *unused)
{
	mutex_lock(&lock_1);
	pr_info("Inside function 1\n");
	msleep(5000);
	mutex_lock(&lock_2);
	msleep(5000);
	mutex_unlock(&lock_2);
	msleep(5000);
	mutex_unlock(&lock_1);
	return 0;
}

static int thread_function2(void *unused)
{
	mutex_lock(&lock_2);
	pr_info("Inside function 2\n");
	msleep(5000);
	mutex_lock(&lock_1);
	msleep(5000);
	mutex_unlock(&lock_1);
	msleep(5000);
	mutex_unlock(&lock_2);
	return 0;
}

static struct task_struct *t1;
static struct task_struct *t2;
asmlinkage long mutex(void *arg)
{
	t1 = kthread_run(thread_function1, NULL, "thread1");
	t2 = kthread_run(thread_function2, NULL, "thread2");
	if (t1 && t2)
		pr_info("Two threads created successfully\n");
	kthread_stop(t1);
	kthread_stop(t2);
	pr_info("Deadlocked inside the mutex_module\n");
	return 0;
}

static int __init init_sys_mutex(void)
{
	pr_info("installed mutex module!\n");
	if (!sysptr_mutex)
		sysptr_mutex = mutex;
	return 0;
}

static void __exit exit_sys_mutex(void)
{
	if (sysptr_mutex)
		sysptr_mutex = NULL;
	pr_info("removed mutex module!\n");
}

module_init(init_sys_mutex);
module_exit(exit_sys_mutex);
MODULE_LICENSE("GPL");
