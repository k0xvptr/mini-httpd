#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>

int main(int argc, char** argv){
	int fd = socket(AF_INET, SOCK_STREAM, 0);  // Initializing the socket() 
	
	// Checking return value of fd
	if (fd < 0) {
		perror("Socket Initialization Failed"); // Error message for debugging
		exit(EXIT_FAILURE);
	}
	struct sockaddr_in addr;
	addr.sin_port = htons(8080); // Assign port and use htons() to convert endianess
	addr.sin_family = AF_INET; // IPv4 address family
	addr.sin_addr.s_addr = htonl(INADDR_ANY); 

	memset(&addr, 0, sizeof(addr)); // initialize everything to zero inside the struct

	// Checking return value of bind()
	if (bind(fd, (struct sockaddr* )&addr, sizeof(addr)) < 0 ) {
		perror("Binding Failed");
		exit(EXIT_FAILURE);
	}

	// Checking return value for listen()
	if (listen(fd, 10) < 0) {
		perror("Listen initialization failed");
		exit(EXIT_FAILURE);
	}
	return 0;
}
