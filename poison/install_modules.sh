#!/bin/sh
set -x
make clean
make
lsmod
rmmod sys_poison
insmod sys_poison.ko
lsmod
