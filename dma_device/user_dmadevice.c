#include <asm/unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/syscall.h>
#include <unistd.h>
#include "dummy_struct.h"

#ifndef __NR_dmadevice
#error dmadevice system call not defined
#endif

int main(int argc, char *argv[])
{
	int rc = 0;
	DUMMY_STRUCT args;
	void *dummy = (void *)(&args);

	rc = syscall(__NR_dmadevice, dummy);
	if (rc == 0)
		printf("syscall returned %d\n", rc);
	else
		printf("syscall returned %d (errno=%d)\n", rc, errno);

	return 0;
}
