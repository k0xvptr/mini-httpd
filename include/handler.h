#ifndef HANDLER_H
#define HANDLER_H

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "trie.h"

void handle_client(int sockfd, struct sockaddr_in *caddr, TrieNode* root);

#endif
