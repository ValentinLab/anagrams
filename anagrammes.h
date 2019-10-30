#ifndef ANAGRAMMES_H
#define ANAGRAMMES_H

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* 
 * ----------------------------------------
 * -> Partie 1 : Strings
 * ----------------------------------------
 */

#define ALPHABET_SIZE 26
#define WILDCARDS_MAX 4

/*
 * Comparer deux strings pour savoir si ce sont des anagrammes
 */
bool string_are_anagrams(const char *str1, const char *str2);

/*
 * Dupliquer une string
 */
char *string_duplicate(const char *str);

/*
 * Trier les letres d'une string (tri par insertion)
 */
void string_sort_letters(char *str);

/*
 * Retirer le caractère de fin de ligne d'un buffer
 */
void clean_newline(char *buf, size_t size);

/* 
 * ----------------------------------------
 * -> Partie 2 : Word array
 * ----------------------------------------
 */

struct word_array {
  char **data;
  size_t size;
  size_t capacity;
};

/*
 * Créer une structure de tableau de mots vide
 */
void word_array_create(struct word_array *self);

/*
 * Détruire une structure de tableau de mots
 */
void word_array_destroy(struct word_array *self);

/*
 * Ajouter un nouveau mot dans un tableau
 */
void word_array_add(struct word_array *self, const char *word);

/*
 * Rechercher les anagrammes d'un mot dans un tableau
 */
void word_array_search_anagrams(const struct word_array *self, const char *word, struct word_array *result);

/*
 * Trier les mots d'un tableau (tri rapide)
 */
void word_array_sort(struct word_array *self);

/*
 * Afficher tous les mots d'un tableau (un par ligne)
 */
void word_array_print(const struct word_array *self);

#define WORD_LETTERS_MAX 32

/*
 * Lire le contenu d'un fichier texte
 */
void word_array_read_file(struct word_array *self, const char *filename);

/* 
 * ----------------------------------------
 * -> Partie 3 : Dictionnary
 * ----------------------------------------
 */

struct word_dict_bucket {
  const char *word;
  struct word_dict_bucket *next;
};

/*
 * Détruire une liste chaînée
 */
void word_dict_bucket_destroy(struct word_dict_bucket *bucket);

/*
 * Ajouter un élément dans une liste chaînée
 */
struct word_dict_bucket *word_dict_bucket_add(struct word_dict_bucket *bucket, const char *word);

struct word_dict {
  struct word_dict_bucket **buckets;
  size_t count;
  size_t size;
};

/*
 * Créer un dictionnaire vide
 */
void word_dict_create(struct word_dict *self);

/*
 * Détruire un dictionnaire
 */
void word_dict_destroy(struct word_dict *self);

#define FNV_OFFSET_BASIS 0xcbf29ce484222325
#define FNV_PRIME 0x00000100000001b3

/*
 * Calculer un hash FNV-1a 64 bits
 */
size_t fnv_hash(const char *key);

/*
 * Effectuer un rehash du dictionnaire
 */
void word_dict_rehash(struct word_dict *self);

/*
 * Ajouter un nouvel élément au dictionnaire
 */
void word_dict_add(struct word_dict *self, const char *word);

/*
 * Remplir un dictionnnaire à partir d'un tableau de mots
 */
void word_dict_fill_with_array(struct word_dict *self, const struct word_array *array);

/*
 * Rechercher les anagrammes d'un mot dans un dictionnaire
 */
void word_dict_search_anagrams(const struct word_dict *self, const char *word, struct word_array *result);

/* 
 * ----------------------------------------
 * -> Partie 4 : Wildcards
 * ----------------------------------------
 */

struct wildcard {
  size_t count;
  size_t index[WILDCARDS_MAX];
};

/*
 * Créer une structure joker
 */
void wildcard_create(struct wildcard *self);

/*
 * Rechercher les jokers dans une chaîne de caractère
 */
void wildcard_search(struct wildcard *self, const char *word);

/*
 * Rechercher les anagrammes d'un mot avec ou sans joker(s) dans un tableau de mots
 */
void word_array_search_anagrams_wildcard(const struct word_array *self, const char *word, struct word_array *result);

/*
 * Rechercher les anagrammes d'un mot avec ou sans joker(s) dans un tableau de mots
 */
void word_dict_search_anagrams_wildcard(const struct word_dict *self, const char *word, struct word_array *result);


#ifdef __cplusplus
}
#endif

#endif // ANAGRAMMES_H
