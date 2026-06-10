#include "../include/server.h"
#include "../include/handler.h"
#include "../include/trie.h"

int main(int argc, char** argv){
	int serverfd = create_server(8080);
  TrieNode* root = trie_header_init();
	while (1) {
		struct sockaddr_in clientaddr;
		socklen_t clen = sizeof(clientaddr);
		int clientfd = accept(serverfd, (struct sockaddr* restrict)&clientaddr, &clen); 
		handle_client(clientfd, &clientaddr, root);
	}
	return 0;
}
