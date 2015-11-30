#include "mapserver.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char** argv)
{
	int listenfd = 0, connfd = 0;
	char* ipaddr = DEFAULT_IP;
	int fd, len, n, err;
	struct sockaddr_in servaddr;
 
    char sendBuff[BSIZE];
    time_t ticks;
	
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
	}

    memset(&servaddr, 0, sizeof(servaddr));
	
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(DEFAULT_PORT);
	inet_aton(ipaddr, &servaddr.sin_addr);
    listenfd = socket(AF_INET, SOCK_STREAM, 0);

	printf("Server ip: %s\n", inet_ntoa(servaddr.sin_addr));
	printf("Server port: %d\n", ntohs(servaddr.sin_port));
	
    bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)); 

    listen(listenfd, 10);
	
    while(1)
    {
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 

        write(connfd, sendBuff, strlen(sendBuff));

        close(connfd);
        sleep(1);
     }
}
