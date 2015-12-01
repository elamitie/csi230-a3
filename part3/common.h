#ifndef COMMON_H
#define COMMON_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

#define DEFAULT_PORT 23032
#define DEFAULT_IP "127.0.0.1"
#define BSIZE 4096

/* protocol */

typedef enum _message_type
{
	MAP,
	ERROR
} message_type;

typedef struct _cli_request
{
	char* msgtype; /* M or E */
	int*  binmsg;  /* Either one or two ints */
	int   binlen;  /* Length of the binary message */
} client_request;

typedef struct _srv_response
{
	char* msgtype;
	char  mapbuff[BSIZE];
	int   errsize;
} server_reponse;

#endif /* COMMON_H */
