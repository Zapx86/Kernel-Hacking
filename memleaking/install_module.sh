#!/bin/sh
set -x
make clean
make
lsmod
rmmod sys_memleaking
insmod sys_memleaking.ko
lsmod
