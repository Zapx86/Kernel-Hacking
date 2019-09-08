obj-m = sys_referencecount.o

INC=/lib/modules/$(shell uname -r)/build/arch/x86/include

all: user kernel_referencecount

user: user_referencecount.c
	gcc -Wall -Werror -I$(INC)/generated/uapi -I$(INC)/uapi user_referencecount.c -o user_referencecount

kernel_referencecount:
	 make -Wall -Werror -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean
	rm -rf user_referencecount

