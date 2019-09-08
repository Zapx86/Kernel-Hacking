obj-m+=sys_stack_sched.o

INC=/lib/modules/$(shell uname -r)/build/arch/x86/include

all: user kernel

user: user_stack_sched.c
	gcc -Wall -Werror -I$(INC)/generated/uapi -I$(INC)/uapi user_stack_sched.c -o user_stack_sched
kernel:
	make -Wall -Werror -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean
	rm -rf user_stack_sched
