#include "mapserver.h"

int main(int argc, char** argv)
{
	int listenfd = 0, connfd = 0;
	char* ipaddr = DEFAULT_IP;
    struct sockaddr_in servaddr;
 
    char sendBuff[1025];
    time_t ticks;
	
	if (argc == 2)
	{
		/* argv contains IP address */
		ipaddr = argv[1];
	}

    memset(&servaddr, 0, sizeof(servaddr));
    memset(sendBuff, 0, sizeof(sendBuff)); 

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

        ticks = time(NULL);
		
		/* TODO: fill sendBuff with the map data in /dev/asciimap */
        snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));
        write(connfd, sendBuff, strlen(sendBuff)); 

        close(connfd);
        sleep(1);
     }
}

