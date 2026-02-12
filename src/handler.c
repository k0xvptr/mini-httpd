#define HEADER_PHASE 0
#define BODY_PHASE 1

#include "../include/handler.h"
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

// A struct that stores data that are header related
typedef struct {
  char method[8];
  char path[256];
  char version[16];

} http_header;

void handle_client(int sockfd, struct sockaddr_in *caddr) {
  http_header data_header;
  const char *term = "\r\n\r\n";
  char buff[4096]; // Initialize a buffer for HTTP client request(s)
  int phase = HEADER_PHASE;
  int term_index =
      -1; // term_index is for the current pos of the terminator "\r\n\r\n" (only for HTTP/1.x)
  while (!phase) {
    ssize_t sz = recv(sockfd, buff, sizeof(buff),
                      0); // Used recv() to read HTTP client request data from kernel buffer
    // Debugging: Show type of error using errno global variable
    if (sz == -1) {
      printf("Error: %d\n", errno);
      exit(errno);
    }
    if (sz == 0) {
      perror("Cannot connect to client");
      exit(errno);
    }

    for (int n = 0; n < sz; ++n) {

      // Check error states for buff[n]
      if (buff[n] != '\r' || buff[n] != '\n') {
        term_index = -1;
      } else if (buff[n] == '\r' && term_index < 0) {
        term_index = 0;

        // Check valid states for buff[n]
      } else if ((buff[n] == '\r' || buff[n] == '\n') && term_index < 3) {
        term_index++;
      } else {
        phase = BODY_PHASE;
        break;
      }
    }
  }

  // TASK FOR TOMORROW: CODE THAT ENABLES ME TO SEPERATE HEADER FROM BODY CONTENT FROM CLIENT HTTP
  // REQUEST
}
