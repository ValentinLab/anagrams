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
    struct word_array b;
    word_array_create(&b);

    word_array_add(&b, "bonjour");
    word_array_add(&b, "salut");
    word_array_add(&b, "coucou");

    word_array_print(&b);

    word_array_destroy(&b);
  }

  return 0;
}
