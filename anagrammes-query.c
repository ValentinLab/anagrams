#include "anagrammes.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define DICT_FILE "dictionnaire.txt"
#define BUFSIZE 512
#define SEC_TO_US 1000000

int main(int argc, char *argv[]) {
  // Lire le fichier dictionnaire
  struct word_array dict_array;
  word_array_create(&dict_array);
  word_array_read_file(&dict_array, DICT_FILE);

  // Vérifier que tous les mots sont dans la tableau de mots
  if(dict_array.size != 325129 + 1) {
    printf("Issue with words number.\n");
    return 1;
  }

  // Créer une structure dictionnaire
  struct word_dict dict;
  word_dict_create(&dict);
  word_dict_fill_with_array(&dict, &dict_array);

  // Rechercher des anagrammes
  char buf[BUFSIZE];
  struct word_array result;
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

    // Temps actuel
    struct timeval init_time;

    /* 
     * ----------------------------------------
     * -> Rechercher via word_array
     * ----------------------------------------
     */

    // Obtenir le temps avant la recherche
    gettimeofday(&init_time, NULL);

    // Rechercher les anagrammes
    word_array_create(&result);
    word_array_search_anagrams(&dict_array, buf, &result);

    // Temps après la recherche
    struct timeval word_array_time;
    gettimeofday(&word_array_time, NULL);
    int word_array_exec_time = (word_array_time.tv_sec * SEC_TO_US + word_array_time.tv_usec) - (init_time.tv_sec * SEC_TO_US + init_time.tv_usec);
    
    word_array_destroy(&result);

    /* 
     * ----------------------------------------
     * -> Rechercher via word_dict
     * ----------------------------------------
     */

    // Obtenir le temps avant la recherche
    gettimeofday(&init_time, NULL);

    // Rechercher les anagrammes
    word_array_create(&result);
    word_dict_search_anagrams(&dict, buf, &result);

    // Obtenir le temps après la recherche
    struct timeval dict_time;
    gettimeofday(&dict_time, NULL);
    int word_dict_exec_time = (dict_time.tv_sec * SEC_TO_US + dict_time.tv_usec) - (init_time.tv_sec * SEC_TO_US + init_time.tv_usec);

    /* 
     * ----------------------------------------
     * -> Afficher les résultats
     * ----------------------------------------
     */

    // Afficher les anagrammes trouvés dans l'ordre alphabétique
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
    printf("--- %d µs (word_array) ---\n", word_array_exec_time);
    printf("--- %d µs (word_dict) ---\n", word_dict_exec_time);

    // Détruire le tableau de mot
    word_array_destroy(&result);
    printf("\n");
  }

  return 0;
}
