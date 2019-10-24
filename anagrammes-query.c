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
    struct word_dict_bucket *b = NULL;

    b = word_dict_bucket_add(b, "bonjour");

    printf("%s", b->word);

    word_dict_bucket_destroy(b);
  }

  return 0;
}
