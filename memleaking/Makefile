obj-m = sys_memleaking.o

INC=/lib/modules/$(shell uname -r)/build/arch/x86/include

all: user kernel_memleaking

user: user_memleaking.c
	gcc -Wall -Werror -I$(INC)/generated/uapi -I$(INC)/uapi user_memleaking.c -o user_memleaking

kernel_memleaking:
	 make -Wall -Werror -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean
	rm -rf user_memleaking

