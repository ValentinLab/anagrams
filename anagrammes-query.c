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
    struct word_dict dict;

    word_dict_create(&dict);

    word_dict_add(&dict, "coucou");
    word_dict_add(&dict, "bonjour");
    word_dict_add(&dict, "salut");

    word_dict_rehash(&dict);

    word_dict_destroy(&dict);

  }

  return 0;
}
