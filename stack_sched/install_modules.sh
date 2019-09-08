#!/bin/sh
set -x
make clean
make
lsmod
rmmod sys_stack_sched
insmod sys_stack_sched.ko
lsmod
