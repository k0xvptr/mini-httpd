#ifndef S_FUNCTIONS_H
#define S_FUNCTIONS_H

typedef enum {
  STATE_METHOD = 0,
  STATE_URL,
  STATE_VERSION,
  STATE_HEADERS,
  STATE_DELIMITER,
  STATE_ERROR = -1,
  STATE_COMPLETE = 100,
} http_states;

// A struct that stores data that are header related
typedef struct {
  char *header_buff; // Buffer that stores the entire request
  int cnt;           // Counter to track current position of pointer
  // Method
  char *method_start;
  char *method_end;
  // URL
  char *url_start;
  char *url_end;
  // Version
  int vcnt;
  char *vstart;
  char *vend;
  // Header Info

}http_header;

http_states method(http_header *header, char byte);
http_states url(http_header *header, char byte);
http_states version(http_header *header, char byte);
http_states header(http_header *header, char byte);

#endif
