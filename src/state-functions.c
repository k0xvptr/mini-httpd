#include "../include/s_functions.h"

#define MAXMETHODLEN 7

http_states method(http_header *header, char byte) {
  header->header_buff[header->cnt] = byte;
  if (header->header_buff[header->cnt] == ' ') {
    header->method_end = &header->header_buff[header->cnt];
    header->cnt++;
    header->url_start = &header->header_buff[header->cnt];
    return STATE_URL;
  } else {
    header->cnt++;
    return STATE_METHOD;
  }
}

http_states url(http_header *header, char byte) {
  header->header_buff[header->cnt] = byte;
  if (header->header_buff[header->cnt] == ' ') {
    header->url_end = &header->header_buff[header->cnt];
    header->cnt++;
    header->vstart = &header->header_buff[header->cnt];
    return STATE_VERSION;
  } else {
    header->cnt++;
    return STATE_URL;
  }
}

http_states version(http_header *header, char byte) {
  const char std_version[8] = "HTTP/1.";
  if (byte != std_version[header->vcnt]) {
    return STATE_ERROR;
  } else {
    header->header_buff[header->cnt] = byte;
    if (header->header_buff[header->cnt] == ' ') {
      header->cnt++;
      return STATE_HEADERS;
    } else {
      header->cnt++;
      return STATE_VERSION;
    }
  }
}
