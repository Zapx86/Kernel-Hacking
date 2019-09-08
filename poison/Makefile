obj-m+=sys_poison.o

INC=/lib/modules/$(shell uname -r)/build/arch/x86/include

all: user kernel

user: user_poison.c
	gcc -Wall -Werror -I$(INC)/generated/uapi -I$(INC)/uapi user_poison.c -o user_poison
kernel:
	make -Wall -Werror -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean
	rm -rf user_poison
