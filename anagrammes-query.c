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

    struct word_array w_a;

    word_array_create(&w_a);

    word_array_add(&w_a, "bonjour");

    word_array_add(&w_a, "hello");

    struct word_dict dict;

    word_dict_create(&dict);

    word_dict_fill_with_array(&dict, &w_a);

    word_dict_destroy(&dict);

    word_array_destroy(&w_a);

  }

  return 0;
}
