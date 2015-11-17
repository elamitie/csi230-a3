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
	int fd, len, n, err, spos = 1000;

	if (argc == 2)
	{
		ascii = argv[1]; // Josh
	}
	else if (argc == 3)
	{
		ascii = argv[1];
		spos = atoi(argv[2]);
	}
	else
		ascii = "josh";

	if ((fd = open("/dev/asciimap", O_RDWR)) >= 0)
	{
		/* do things */
		len = strlen(ascii);
		err = lseek(fd, spos, SEEK_SET);
		if (err < 0)
			printf("Seek was out of bounds!\n");
		write(fd, ascii, len);
		printf("Writing %s to driver..\n", ascii);
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
