#define MAX_METHODLEN 8
#define MAX_URLLEN 6000

#include "../include/handler.h"
#include "../include/url_fns.h"
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
  int cnt;
  // Method 
  char *method_start;
  char *method_end;
  // URL
  char* url_start;
  char* path_end;
  char* qstr;
  char* url_end;
} __attribute__((packed)) http_header;

typedef enum {
  STATE_START = 1,
  STATE_METHOD,
  STATE_URL,
  STATE_URL_PARSE,
  STATE_DELIMITER,
  STATE_ERROR = -1,
  STATE_COMPLETE = 0,
} http_states;

void handle_client(int sockfd, struct sockaddr_in *caddr) {
  char buff[1024];
  const char *delimiter = "\r\n\r\n";
  int dcnt = 0;
  http_header *content;
  content->header_buff = (char *)malloc(10000 * sizeof(char));
  content->method_start = 0;
  content->cnt = 0;
  http_states state = STATE_START;
  while (state != STATE_COMPLETE && state != STATE_ERROR && content->cnt < sizeof(content->header_buff)) {
    char* fake_req = "GET /index.html HTTP/1.1\r\n";
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
              content->header_buff[content->cnt] = buff[i];
              content->cnt++;
              state = STATE_METHOD;
              break;
            default:
              state = STATE_ERROR;
              break;
          }
          break;
        case STATE_METHOD:
          if (buff[i] != ' ') {
            content->header_buff[content->cnt] = buff[i];
            content->cnt++;
          } else {
            switch (content->header_buff[0]) {
              case 'G':
                if (memcmp(content->header_buff, "GET", 3) == 0) {
                  content->method_start = content->header_buff;
                  content->method_end = &content->header_buff[content->cnt];
                  state = STATE_URL;
                  break;
                } else {
                  state = STATE_ERROR;
                  break;
                }
              case 'P':
                __asm__ volatile ("nop");
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
          if (content->header_buff[content->cnt] == ' ') {
            content->cnt++;
            content->url_start = &content->header_buff[content->cnt];
          } else {
            if (content->cnt >= MAX_URLLEN) {
              state = STATE_ERROR;
            }
            if (buff[i] == ' ') {
              content->cnt++;
              content->url_end = &content->header_buff[content->cnt];
              state = STATE_URL_PARSE;
            } else {
              content->cnt++;
            }
          }
        case STATE_URL_PARSE:
          __asm__ volatile ("nop");
          void (*handler[2])(int) = { game, pdf };
        case STATE_DELIMITER:
               
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
