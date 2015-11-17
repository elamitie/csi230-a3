#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "common.h"

int main(argc, argv)
	int argc;
	char* argv[];
{
	char buf[BSIZE];
	char* ascii;
	int len;
	int fd, i, j, n;

	if ((fd = open("/dev/asciimap", O_RDWR)) >= 0)
	{
		/* do things */
		ascii = "josh"; 	
		len = strlen(ascii);
		write(fd, ascii, len);
		n = read(fd, buf, BSIZE);
		printf(buf);
		close(fd);
	}
	else
	{
		perror("/dev/asciimap failed");
		exit(1);
	}

	exit(0);
}
