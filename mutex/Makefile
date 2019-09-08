obj-m+=sys_mutex.o

INC=/lib/modules/$(shell uname -r)/build/arch/x86/include

all: user kernel

user: user_mutex.c
	gcc -Wall -Werror -I$(INC)/generated/uapi -I$(INC)/uapi user_mutex.c -o user_mutex
kernel:
	make -Wall -Werror -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean
	rm -rf user_mutex
