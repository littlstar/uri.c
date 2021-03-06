
/**
 * `test.c' - uri
 *
 * copyright (c) 2014 joseph werle
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ok/ok.h>

#include "uri.h"

#define S(x) # x
#define t(m, a, b) ({                              \
    char tmp[1024];                                \
    sprintf(tmp, "%s(%s) = %s", S(m), S(a), S(b)); \
    char *result = m(a);                           \
    assert(0 == strcmp(b, result));                \
    ok(tmp);                                       \
    free(result);                                  \
})

int
main (void) {

  // encode
  {
    t(uri_encode,
        "Betty's favorite language is Français",
        "Betty%27s%20favorite%20language%20is%20Fran%C3%A7ais");

    t(uri_encode, "(45 * 2) + 90", "(45%20*%202)%20%2B%2090");

    t(uri_encode,
        "`console.log(value); if (!foo) { _bar(): }`",
        "%60console.log(value)%3B%20if%20(!foo)%20%7B%20_bar()%3A%20%7D%60");

    t(uri_encode,
        "\"it will all be alright !\", he said.",
        "%22it%20will%20all%20be%20alright%20!%22%2C%20he%20said.");
  }

  // decode
  {
    t(uri_decode,
        "a%C3%A7%C3%BAcar",
        "açúcar");

    t(uri_decode,
        "tor%C3%A7ut",
        "torçut");

    t(uri_decode,
        "JavaScript_%D1%88%D0%B5%D0%BB%D0%BB%D1%8B",
        "JavaScript_шеллы");
  }

  ok_done();
  return 0;
}
