obj-m = sys_sgdebugging.o

INC=/lib/modules/$(shell uname -r)/build/arch/x86/include

all: user kernel_sgdebugging

user: user_sgdebugging.c
	gcc -Wall -Werror -I$(INC)/generated/uapi -I$(INC)/uapi user_sgdebugging.c -o user_sgdebugging

kernel_sgdebugging:
	 make -Wall -Werror -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean
	rm -rf user_sgdebugging

