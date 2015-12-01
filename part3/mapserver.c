#include "mapserver.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char** argv)
{
	int listenfd = 0, connfd = 0;
	char* ipaddr = DEFAULT_IP;
	int fd, n;
	struct sockaddr_in servaddr;
	struct sockaddr_in cliaddr;
	socklen_t clilen;

    char sendBuff[BSIZE];
	char recvBuff[1025];

	char* delim = " ";
	char* token;
	char* msgtype;
	int*  msgparams;
	int   i = 0;
	
	if (argc == 2)
	{
		/* argv contains IP address */
		ipaddr = argv[1];
	}

	memset(sendBuff, 0, sizeof(sendBuff));
	
	/* Load the ascii map into the buffer to send
	   to the client */
	fd = open("/dev/asciimap", O_RDWR);
	if (fd >= 0)
	{
		n = read(fd, sendBuff, BSIZE);
	}
	else
	{
		printf("Error reading from driver, error: %s\n", strerror(errno));
		printf("Remember, you need to be root to read from the driver!\n");
		printf("Also, don't forget to mount the driver.\n");
	}

    memset(&servaddr, 0, sizeof(servaddr));
	
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(DEFAULT_PORT);
	inet_aton(ipaddr, &servaddr.sin_addr);
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
	
    bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)); 

    listen(listenfd, 10);

	clilen = sizeof(cliaddr);
	connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &clilen);
	n = read(connfd, recvBuff, sizeof(recvBuff)-1);

	/* Parse packet data from recvBuff */
	token = strtok(recvBuff, delim);
	//msgtype = token;
	
	/* Allocate msgparams to the most possible, width + height */
    msgparams = malloc(sizeof(int) * 2);
	
	while (token != NULL)
	{
		if (i == 0)
			msgtype = token;
		else
			msgparams[--i] = atoi(token);

		i++;
		token = strtok(NULL, delim);
	}

	/* Do something with the params */
	if (i == 1) /* Only one was received */
	{
		write(connfd, sendBuff, strlen(sendBuff));
	}
	else        /* Width and height were received */
	{
		printf("Oops not implemented yet (and never will be!) :D\n");
	}

	return 0;
	
	/*
    while(1)
    {
        connfd = accept(listenfd, (struct sockaddr*)cliaddr, &clilen); 

        write(connfd, sendBuff, strlen(sendBuff));

        close(connfd);
        sleep(1);
     }
	*/
}
