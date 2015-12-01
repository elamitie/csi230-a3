#include "mapserver.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

int main(int argc, char** argv)
{
    int listenfd = 0, connfd = 0;
    char* ipaddr = DEFAULT_IP;
    int fd, n;
    FILE *log_file;
    struct sockaddr_in servaddr;
    struct sockaddr_in cliaddr;
    socklen_t clilen;

    char sendBuff[BSIZE];//Can be smaller
    char mapBuff[BSIZE];
    char recvBuff[1025];

    char* delim = "~";
    char* token;
    char* msgtype;
    char* errmsg;
    char* errlen;
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
	n = read(fd, mapBuff, BSIZE);
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
	
    log_file = fopen("server_log.txt", "a");
    if( log_file == NULL)
    {
	perror("error opening log file");
	return -1;
    }
			
    while(1)
    {

	clilen = sizeof(cliaddr);

	connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &clilen);
	n = read(connfd, recvBuff, sizeof(recvBuff)-1);

	/* Parse packet data from recvBuff */
	token = strtok(recvBuff, delim);
	//msgtype = token;
	
	/* Allocate msgparams to the most possible, width + height */
	msgparams = malloc(sizeof(int) * 2);
	i = 0;	
	while (token != NULL)
	{
	    if (i == 0)
	        msgtype = token; 
	    else
		msgparams[i - 1] = atoi(token);

	    i++;
	    token = strtok(NULL, delim);
	}

	//I goes one extra time
	i--;

	/* Do something with the params */
	if (i == 1) /* Only one was received */
	{
	    if(msgparams[0] != 0)
	    {	
	        throwError(sendBuff, "Error: Expected 0 in param[0]");
		logMessage(log_file, "Error: Expected 0 in param[0]");
		write(connfd, sendBuff, strlen(sendBuff));
	    }
	    else
	    {
	        printf("Sending map to client\n");
	       	logMessage(log_file, "Sending map to client");
		strcpy(sendBuff, "M~50~50~");
		strcat(sendBuff, mapBuff);
		write(connfd, sendBuff, strlen(sendBuff));
	    }
	}
	else if(i == 2)	       /* Width and height were received */
	{
	    logMessage("Not Implemented Exception!");
	    printf("Not Implemented Exception!");		
	}
	else /* Error case  */
	{
	    throwError(sendBuff, "Error: Unknown Protocol");
	    logMessage(log_file, "Error: Unknown Protocol");
	    write(connfd, sendBuff, strlen(sendBuff));
	}
		

	close(connfd);
	sleep(1);

    }//End of the the while loop

    fclose(log_file);

    return 0;
}

int
throwError(char sendBuff[], char* errmsg)
{
    char* errlen = malloc(strlen(errmsg));

    sprintf(errlen, "%d", strlen(errmsg));
    strcpy(sendBuff, "E~");
    strcat(sendBuff, errlen);
    strcat(sendBuff, "~");
    strcat(sendBuff, errmsg);
    strcat(sendBuff, "\n");
    perror(errmsg);
    return 0;
}

int logMessage(FILE* log_file, char* msg)
{
    char* time_string;
    time_t current_time;

    current_time = time(NULL);

    if(current_time == ((time_t)-1))
    {
        perror("Failed to get time");
	return -1;
    }
	
    time_string = ctime(&current_time);

    if(time_string == NULL)
    {
        perror("Failed to convert time to string");
	return -1;
    }
    
    fprintf(log_file, "%s", time_string);
    fprintf(log_file, "	%s", msg);
    fprintf(log_file, "%s", "\n");
    fflush(log_file);

    return 0;
}



