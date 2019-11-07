#include "anagrammes.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define DICT_FILE "dictionnaire.txt"
#define DICT_WORD_NUMBER 325129
#define BUFSIZE 512
#define SEC_TO_US 1000000

/*
 * Afficher le nombre d'anagrammes et le temps d'exécution
 */
static void print_results_data(struct word_array *result, struct timeval *before, struct timeval *after) {
  // Calculer le temps d'exécution
  int exec_time = (after->tv_sec * SEC_TO_US + after->tv_usec) - (before->tv_sec * SEC_TO_US + before->tv_usec);

  // Afficher le nombre d'anagrammes et le temps
  printf("\n--- Result : %ld anagram", result->size);
  if(result->size > 1) {
    printf("s");
  }
  printf(" found\n");
  printf("--- Time   : %d µs\n\n", exec_time);
}

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

  // Afficher le message d'accueil
  printf("FIND ANAGRAMS\nInfo: exit the application by entering an empty word.\n\n");

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
    printf("\n");

    // Vérifier si le mot est vide et quitter le programme dans ce cas
    if(buf[0] == '\0') {
      word_array_destroy(&dict_array);
      word_dict_destroy(&dict);
      return 0;
    }

    // Temps avant et après la recherche (avant la recherche des anagrammes)
    struct timeval init_time;
    struct timeval exec_time;
    // Tableau de mots contenant les anagrammmes
    struct word_array result;

    /* 
     * ----------------------------------------
     * -> Rechercher via word_dict
     * ----------------------------------------
     */

     // Obtenir le temps avant la recherche
    gettimeofday(&init_time, NULL);

    // Rechercher les anagrammes
    word_array_create(&result);
    word_array_search_anagrams_wildcard(&dict_array, buf, &result);

    // Obtenir le temps après la recherche
    gettimeofday(&exec_time, NULL);

    // Afficher le résultat
    word_array_print(&result);
    printf("\n--- word_array");
    print_results_data(&result, &init_time, &exec_time);

    word_array_destroy(&result);

    /* 
     * ----------------------------------------
     * -> Rechercher via word_array
     * ----------------------------------------
     */

    // Obtenir le temps avant la recherche
    gettimeofday(&init_time, NULL);

    // Rechercher les anagrammes
    word_array_create(&result);
    word_dict_search_anagrams_wildcard(&dict, buf, &result);
    // Trier le tableau result
    word_array_sort(&result);

    // Obtenir le temps après la recherche
    gettimeofday(&exec_time, NULL);

    // Afficher le résultat
    word_array_print(&result);
    printf("\n--- word_dict");
    print_results_data(&result, &init_time, &exec_time);

    word_array_destroy(&result);
  }

  return 0;
}
