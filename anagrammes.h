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
 * Initialiser une structure de tableau de mots
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
 * Trier les mpts d'un tableau (tri rapide)
 */
void word_array_sort(struct word_array *self);

/*
 * Afficher tous les mots d'un tableau (un par ligne)
 */
void word_array_print(const struct word_array *self);

#define WORD_LETTERS_MAX 32

/*
 * Lire le contenu d'un fichier
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

void word_dict_bucket_destroy(struct word_dict_bucket *bucket);

struct word_dict_bucket *word_dict_bucket_add(struct word_dict_bucket *bucket, const char *word);

struct word_dict {
  struct word_dict_bucket **buckets;
  size_t count;
  size_t size;
};

void word_dict_create(struct word_dict *self);

void word_dict_destroy(struct word_dict *self);

size_t fnv_hash(const char *key);

void word_dict_rehash(struct word_dict *self);

void word_dict_add(struct word_dict *self, const char *word);

void word_dict_fill_with_array(struct word_dict *self, const struct word_array *array);

void word_dict_search_anagrams(const struct word_dict *self, const char *word, struct word_array *result);

/* 
 * ----------------------------------------
 * -> Partie 4 : Wildcards
 * ----------------------------------------
 */

#define WILDCARDS_MAX 3

struct wildcard {
  size_t count;
  size_t index[WILDCARDS_MAX];
};

void wildcard_create(struct wildcard *self);

void wildcard_search(struct wildcard *self, const char *word);

void word_array_search_anagrams_wildcard(const struct word_array *self, const char *word, struct word_array *result);

void word_dict_search_anagrams_wildcard(const struct word_dict *self, const char *word, struct word_array *result);


#ifdef __cplusplus
}
#endif

#endif // ANAGRAMMES_H
