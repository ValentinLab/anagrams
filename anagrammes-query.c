#include "anagrammes.h"

#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 512

int main(int argc, char *argv[]) {
  char buf[BUFSIZE];

  for (;;) {
    printf("Letters: ");
    fgets(buf, BUFSIZE, stdin);
    clean_newline(buf, BUFSIZE);

    /*
     * ******************************
     * TEST
     * *****************************
     */
    printf("%lx\n", fnv_hash(buf));

  }

  return 0;
}
