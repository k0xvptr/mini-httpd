#define MAX_METHODLEN 8

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
  char *header_buff;
  int buffcnt;
  // Method 
  char *method_start;
  char *method_end;
  // URL
  char* url_start;
  char* url_end;
} __attribute__((packed)) http_header;

typedef enum {
  STATE_START = 1,
  STATE_METHOD,
  STATE_URL,
  STATE_PARSE,
  STATE_ERROR = -1,
  STATE_COMPLETE = 0,
} http_states;

void handle_client(int sockfd, struct sockaddr_in *caddr) {
  char buff[1024];
  const char *delimiter = "\r\n\r\n";
  http_header *content;
  content->header_buff = (char *)malloc(10000 * sizeof(char));
  content->method_start = 0;
  content->buffcnt = 0;
  http_states state = STATE_START;
  while (state != STATE_COMPLETE && state != STATE_ERROR && content->buffcnt < sizeof(content->header_buff)) {
    char* fake_req = "GET ./index.html HTTP/1.1\r\n";
    strcpy(buff, fake_req);
    int bytes = strlen(fake_req);
    if (bytes <= 0) {
      printf("error\n");
    }
    for (int i = 0; i < bytes; ++i) {
      switch (state) {
      case STATE_START:
        switch (buff[i]) {
        case 'D':
        case 'H':
        case 'O':
        case 'C':
        case 'T':
        case 'G':
        case 'P':
          content->header_buff[content->buffcnt] = buff[i];
          content->buffcnt++;
          state = STATE_METHOD;
          break;
        default:
          state = STATE_ERROR;
          break;
        }
        break;
      case STATE_METHOD:
        if (buff[i] != ' ') {
          content->header_buff[content->buffcnt] = buff[i];
          content->buffcnt++;
        } else {
          switch (content->header_buff[0]) {
          case 'G':
            if (memcmp(content->header_buff, "GET", 3) == 0) {
              content->method_start = content->header_buff;
              content->method_end = &content->header_buff[content->buffcnt];
              state = STATE_URL;
              break;
            } else {
              state = STATE_ERROR;
              break;
            }
          case 'P':
            char *list[] = {"POST", "PUT"};
            for (int it = 0; it < 2; ++i) {
              if (memcmp(content->header_buff, list[it], strlen(list[it])) == 0) {
                content->method_start = content->header_buff;
                content->method_end = content->header_buff + strlen(list[it]);
                state = STATE_URL;
                break;
              }
            }
          }
        }
        break;

      case STATE_URL:
        if (content->header_buff[content->buffcnt] == ' ') {
          content->buffcnt++;
          content->url_start = &content->header_buff[content->buffcnt];
        } else {
          if (buff[i] == ' ') {
            content->buffcnt++;
            content->url_end = &content->header_buff[content->buffcnt];
          } else {
            content->buffcnt++;
          }
        }
      case STATE_PARSE:

      case STATE_ERROR:
        printf("Error\n");
      case STATE_COMPLETE:
        printf("Complete\n");
        break;
      }
    }
  }
  free(content);
}

int main() {
  handle_client(0, NULL);
  return 0;
}
