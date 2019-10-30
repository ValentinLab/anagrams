#include "anagrammes.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define DICT_FILE "dictionnaire.txt"
#define DICT_WORD_NUMBER 325129 + 1
#define BUFSIZE 512
#define SEC_TO_US 1000000

int main(int argc, char *argv[]) {
  // Lire le fichier dictionnaire
  struct word_array dict_array;
  word_array_create(&dict_array);
  word_array_read_file(&dict_array, DICT_FILE);

  // Vérifier que tous les mots du fichier sont dans dict_array
  if(dict_array.size != DICT_WORD_NUMBER) {
    printf("Issue with words number.\n");
    return 1;
  }

  // Créer une structure dictionnaire et la remplir avec dict_array
  struct word_dict dict;
  word_dict_create(&dict);
  word_dict_fill_with_array(&dict, &dict_array);

  // Faire saisir des lettres à l'utilisateur et rechercher les anagrammes
  char buf[BUFSIZE];
  for(;;) {
    /* 
     * ----------------------------------------
     * -> Obtenir la saisie de l'utilisateur
     * ----------------------------------------
     */

    // Demander à l'utilisateur de saisir des lettres
    printf("Letters: ");
    fgets(buf, BUFSIZE, stdin);
    clean_newline(buf, BUFSIZE);

    // Vérifier si le mot est vide et quitter le programme dans ce cas
    if(buf[0] == '\0') {
      word_array_destroy(&dict_array);
      word_dict_destroy(&dict);

      return 0;
    }

    // Temps actuel (avant la recherche des anagrammes)
    struct timeval initial_time;

    // Tableau de mots contenant les anagrammmes
    struct word_array result;

    /* 
     * ----------------------------------------
     * -> Rechercher via word_dict
     * ----------------------------------------
     */

    // Obtenir le temps avant la recherche
    gettimeofday(&initial_time, NULL);

    // Rechercher les anagrammes
    word_array_create(&result);
    word_dict_search_anagrams_wildcard(&dict, buf, &result);

    // Obtenir le temps après la recherche
    struct timeval time_dict;
    gettimeofday(&time_dict, NULL);
    int word_dict_exec_time = (time_dict.tv_sec * SEC_TO_US + time_dict.tv_usec) - (initial_time.tv_sec * SEC_TO_US + initial_time.tv_usec);

    // Afficher les anagrammes trouvées dans l'ordre alphabétique
    word_array_sort(&result);
    word_array_print(&result);

    // Afficher le nombre d'anagrammes et le temps
    printf("\n--- %ld ", result.size);
    if(result.size > 1) {
      printf("anagrams");
    } else {
      printf("anagram");
    }
    printf(" found ---\n");
    printf("--- %d µs (word_dict) ---\n", word_dict_exec_time);

    word_array_destroy(&result);
    printf("\n");

    /* 
     * ----------------------------------------
     * -> Rechercher via word_array
     * ----------------------------------------
     */

    // Obtenir le temps avant la recherche
    gettimeofday(&initial_time, NULL);

    // Rechercher les anagrammes
    word_array_create(&result);
    word_array_search_anagrams_wildcard(&dict_array, buf, &result);

    // Temps après la recherche
    struct timeval time_word_array;
    gettimeofday(&time_word_array, NULL);
    int word_array_exec_time = (time_word_array.tv_sec * SEC_TO_US + time_word_array.tv_usec) - (initial_time.tv_sec * SEC_TO_US + initial_time.tv_usec);

    // Afficher les anagrammes trouvées dans l'ordre alphabétique
    word_array_print(&result);

    // Afficher le nombre d'anagrammes et le temps
    printf("\n--- %ld ", result.size);
    if(result.size > 1) {
      printf("anagrams");
    } else {
      printf("anagram");
    }
    printf(" found ---\n");
    printf("--- %d µs (word_array) ---\n", word_array_exec_time);
    printf("\n");

    word_array_destroy(&result);
  }

  return 0;
}
