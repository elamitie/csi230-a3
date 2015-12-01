#include "mapclient.h"

int main(int argc, char** argv)
{
    int sockfd = 0, n = 0;
    char* ipaddr = DEFAULT_IP;
    int port = DEFAULT_PORT;
    char recvBuff[BSIZE];
    struct sockaddr_in servaddr;
    char* delim = "~";
    char* token;
    char* msgtype;
    int* msgparams;
    char recvstr[BSIZE];
    int i = 0;

    FILE* log_file;

    client_request request;

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

    log_file = fopen("client_log.txt", "a");

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
	
    char* default_msg = "";
    char client_msg[256];

    /* read the request from the user */
    printf("Enter your message (spaced by ~): ");
    scanf("%s",client_msg);
    printf("\n");

    /* request a map from the server */
    write(sockfd, client_msg, strlen(client_msg));
	
    n = read(sockfd, recvBuff, sizeof(recvBuff)-1); 
    if (n >= 0)
    {
        token = strtok(recvBuff, delim);
		
	msgparams = malloc(sizeof(int) * 2);
		
	while(token != NULL)
       	{
		
	    if(i == 0)
	        msgtype = token;
	    else if(i == 1 || (i == 2 && strcmp(msgtype,"M") == 0))
	        msgparams[i - 1] = atoi(token);
	    else
	        strcpy(recvstr, token);

	    i++;
	    token = strtok(NULL, delim);
       	}
		
	if(strcmp(msgtype, "M") == 0)
	{
	    printf(recvstr);
	    logMessage(log_file,"Map recieved");
	}
	else
	{
	    printf(recvstr);
	    logMessage(log_file, recvstr);
	}
    }
    else
    {
        logMessage(log_file, "Error reading from socket");
	printf("Error reading from socket: %s\n", strerror(errno));
    }
   
    memset(recvBuff, 0, sizeof(recvBuff)); 
    n = read(sockfd, recvBuff, sizeof(recvBuff) - 1);
    printf(recvBuff);

    fclose(log_file);
    return 0;
}

int logMessage(FILE* log_file, char* msg)
{
    char* time_string;
    time_t current_time;

    current_time = time(NULL);
   
    time_string = ctime(&current_time);

    fprintf(log_file,"%s", time_string);
    fprintf(log_file,"	%s", msg);
    fprintf(log_file, "%s", "\n");
    fflush(log_file);

    return 0;
}
