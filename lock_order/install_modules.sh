#!/bin/sh
set -x
make clean
make
rmmod sys_lockorder
insmod sys_lockorder.ko
