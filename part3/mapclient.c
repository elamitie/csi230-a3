#include "mapclient.h"

int main(int argc, char** argv)
{
	int sockfd = 0, n = 0;
	char* ipaddr = DEFAULT_IP;
	int port = DEFAULT_PORT;
	char recvBuff[BSIZE];
    struct sockaddr_in servaddr; 

    if(argc == 2)
	{
		/* IP was passed via command line */
		ipaddr = argv[1];
	}

    memset(recvBuff, 0, sizeof(recvBuff));
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    } 

    memset(&servaddr, 0, sizeof(servaddr)); 

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port); 
	
    if(inet_pton(AF_INET, ipaddr, &servaddr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    } 

    if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
		printf("\n Error : Connect Failed %s\n", strerror(errno));
		return 1;
    } 

	/*
    while ( (n = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0)
    {
        recvBuff[n] = 0;
        if(fputs(recvBuff, stdout) == EOF)
        {
            printf("\n Error : Fputs error\n");
        }
	}*/

	n = read(sockfd, recvBuff, sizeof(recvBuff)-1);
	if (n >= 0)
	{
		printf(recvBuff);
	}
	else
	{
		printf("Error reading from socket: %s\n", strerror(errno));
	}

    return 0;
}
