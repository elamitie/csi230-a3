#ifndef COMMON_H
#define COMMON_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

#define DEFAULT_PORT 23032
#define DEFAULT_IP "127.0.0.1"
#define BSIZE 4096

#endif /* COMMON_H */
