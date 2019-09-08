#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <string.h>
#ifndef __NR_memleaking
#error memleaking system call not defined
#endif

int main(int argc, char *argv[])
{
	int rc;
	int num = 4;
	void *dummy = (void *)&num;

	rc = syscall(__NR_memleaking, dummy);
	goto exit;
exit:
	if (rc == 0)
		printf("syscall returned %d\n", rc);
	else
		printf("syscall returned %d (errno=%d)\n", rc, errno);
	exit(rc);
}
