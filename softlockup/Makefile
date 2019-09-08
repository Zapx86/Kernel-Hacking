obj-m+=sys_softlockup.o

INC=/lib/modules/$(shell uname -r)/build/arch/x86/include

all: user kernel

user: user_softlockup.c
	gcc -Wall -Werror -I$(INC)/generated/uapi -I$(INC)/uapi user_softlockup.c -o user_softlockup
kernel:
	make -Wall -Werror -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean
	rm -rf user_softlockup
