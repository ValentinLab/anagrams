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

  // Vérifier que tous les mots sont dans la tableau de mots
  if(dict_array.size != 325129 + 1) {
    printf("Le nombre de mots est incorrecte.\n");
    return 1;
  }

  // Créer une structure dictionnaire
  struct word_dict dict;
  word_dict_create(&dict);
  word_dict_fill_with_array(&dict, &dict_array);

  // Rechercher des anagrammes
  char buf[BUFSIZE];
  struct word_array result;
  do {
    // Demander à l'utilisateur de saisir des lettres
    printf("Letters: ");
    fgets(buf, BUFSIZE, stdin);
    clean_newline(buf, BUFSIZE);

    // Rechercher les anagrammes
    word_array_create(&result);
    word_dict_search_anagrams(&dict, buf, &result);

    // Afficher les résultats
    word_array_print(&result);

    word_array_destroy(&result);
    printf("\n");

  } while(buf[0] != '\0');

  // Détruire les structures
  word_array_destroy(&dict_array);
  word_dict_destroy(&dict);

  return 0;
}
