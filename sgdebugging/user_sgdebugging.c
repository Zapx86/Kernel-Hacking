#include <asm/unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/syscall.h>
#include <unistd.h>
#ifndef __NR_sgdebugging
#error sgdebugging system call not defined
#endif

int main(int argc, char *argv[])
{
	int rc;
	int num = 4;
	void *dummy = (void *)&num;

	rc = syscall(__NR_sgdebugging, dummy);
	goto exit;
exit:
	if (rc == 0)
		printf("syscall returned %d\n", rc);
	else
		printf("syscall returned %d (errno=%d)\n", rc, errno);
	exit(rc);
}
