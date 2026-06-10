#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>

int create_server(int port);

#endif
