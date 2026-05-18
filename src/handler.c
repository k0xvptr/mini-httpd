#define MAX_METHODLEN 8
#define MAX_URLLEN 6000

#include "../include/handler.h"
#include "../include/s_functions.h"

typedef http_states (*state_fn)(http_header* header, char byte);

void handle_client(int sockfd, struct sockaddr_in *caddr) {
  char buff[1024];
  const char delimiter[4] = "\r\n\r\n";
  state_fn s_functions[3] = {
    method, url, version
  };
  http_header *content = malloc(sizeof(http_header));
  content->header_buff = (char *)malloc(100000 * sizeof(char));
  content->method_start = 0;
  content->cnt = 0;
  http_states state = STATE_METHOD;
  while (state != STATE_COMPLETE && state != STATE_ERROR) {
    char* fake_req = "GET /index.html HTTP/1.1\r\n";
    strcpy(buff, fake_req);
    int bytes = strlen(fake_req);
    if (bytes <= 0) {
      printf("error\n");
    }
    for (int i = 0; i < bytes; ++i) {
       state = s_functions[state](content, buff[i]);  
    }
  } 
}

int main() {
  handle_client(0, NULL);
  return 0;
}
