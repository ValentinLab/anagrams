#include "anagrammes.h"

#include <stdio.h>
#include <stdlib.h>

#define DICT_FILE "dictionnaire.txt"
#define BUFSIZE 512

int main(int argc, char *argv[]) {
  // Lire le fichier dictionnaire
  struct word_array dict_array;
  word_array_create(&dict_array);
  word_array_read_file(&dict_array, DICT_FILE);

  // Créer un dictionnaire
  struct word_dict dict;
  word_dict_create(&dict);
  word_dict_fill_with_array(&dict, &dict_array);

  // Proposer la saisie de lettres
  char buf[BUFSIZE];
  for (;;) {
    printf("Letters: ");
    fgets(buf, BUFSIZE, stdin);
    clean_newline(buf, BUFSIZE);
  }

  // Détruire les structures
  word_array_destroy(&dict_array);
  word_dict_destroy(&dict);

  return 0;
}
