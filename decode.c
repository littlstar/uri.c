
/**
 * `decode.c' - uri
 *
 * copyright (c) 2014 joseph werle
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "uri.h"

char *
uri_decode (const char *src) {
  int i = 0;
  size_t size = 0;
  size_t len = 0;
  char *dec = NULL;
  char tmp[3];
  char ch = 0;

  // alloc
  dec = (char *) malloc(0);
  if (NULL == dec) { return NULL; }

  // chars len
  len = strlen(src);

#define push(c) (dec = (char *) realloc(dec, size + 1), dec[size++] = c)

  // decode
  while (len--) {
    ch = src[i++];

    // if prefix `%' then read byte and decode
    if ('%' == ch) {
      tmp[0] = src[i++];
      tmp[1] = src[i++];
      tmp[2] = '\0';
      push(strtol(tmp, NULL, 16));
    } else {
      push(ch);
    }
  }

  dec[size] = '\0';

#undef push

  return dec;
}