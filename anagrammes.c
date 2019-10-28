#include "anagrammes.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 
 * ----------------------------------------
 * -> Partie 1 : Strings
 * ----------------------------------------
 */

bool string_are_anagrams(const char *str1, const char *str2) {
  assert(str1 != NULL);
  assert(str2 != NULL);

  // Taille des chaînes de caractères
  const size_t alphabet_size = 26;
  size_t size_str = strlen(str1);

  // Comparer la taille des deux chaînes
  if(size_str != strlen(str2)) {
    return false;
  }

  // Compter les occurences de chaque lettre pout str1 et str2
  int *count_letters = calloc(alphabet_size, sizeof(int));
  if(count_letters == NULL) {
    printf("Problème lors de l'allocation de la mémoire.\n");
    return false;
  }
  for(size_t i = 0; i < size_str; ++i) {
    count_letters[str1[i] - 'a'] += 1;
    count_letters[str2[i] - 'a'] -= 1;
  }

  // Contrôler les occurences des deux strings
  size_t index = 0;
  while(index < alphabet_size) {
    if(count_letters[index] != 0) {
      free(count_letters);
      return false;
    }
    ++index;
  }

  free(count_letters);

  return true;
}

char *string_duplicate(const char *str) {
  assert(str != NULL);

  // Allouer la mémoire nécessaire à la nouvelle chaîne
  char *str_cpy = malloc(strlen(str) * sizeof(char) + 1);
  if(str_cpy == NULL) {
    printf("Problème lors de l'allocation de la mémoire.\n");
    return NULL;
  }

  // Copier str dans la nouvelle chaîne
  strcpy(str_cpy, str);

  return str_cpy;
}

void string_sort_letters(char *str) {
  assert(str != NULL);

  // Taille de la chaîne à trier
  size_t size = strlen(str);

  // Parcourir l'ensemble de la chaîne de caractères
  for(size_t i = 1; i < size; ++i) {
    // Lettre courante
    int value = str[i];

    // Trouver le bon indice du caractère
    size_t j = i;
    while(j > 0 && str[j - 1] > value) {
      str[j] = str[j - 1];
      --j;
    }

    // Insérer la lettre courante au bon indice
    str[j] = value;
  }
}

void clean_newline(char *buf, size_t size) {
  assert(buf != NULL);
  assert(size != 0);

  // Rechercher l'indice du caractère de fin de ligne
  size_t i = 0;
  while(i < size - 1 && buf[i] != '\n') {
    ++i;
  }

  // Remplacer le caractère par celui de fin de chaîne
  buf[i] = '\0';
}

/* 
 * ----------------------------------------
 * -> Partie 2 : Word array
 * ----------------------------------------
 */

void word_array_create(struct word_array *self) {
  assert(self != NULL);

  // Allouer un tableau de capacité 10 et taille 0
  self->data = calloc(10, sizeof(char *));
  self->size = 0;
  self->capacity = 10;
}

void word_array_destroy(struct word_array *self) {
  assert(self != NULL);

  // Libérer la mémoire de tous les mots présents dans la tableau
  for(size_t i = 0; i < self->size; ++i) {
    free(self->data[i]);
  }

  // Libérer la mémoire du tableau
  free(self->data);
  self->data = NULL;
  self->capacity = 0;
  self->size = 0;
}

/*
 * Augmenter la capacité du tableau de mots
 */
static void word_array_grow(struct word_array *self) {
  assert(self != NULL);

  // Doubler la capacité du tableau
  self->capacity *= 2;

  // Allouer la mémoire du nouveau tableau et le remplir
  char **data = calloc(self->capacity, sizeof(char *));
  memcpy(data, self->data, self->size * sizeof(char *));
  
  // Remplacer l'ancien tableau
  free(self->data);
  self->data = data;
}

void word_array_add(struct word_array *self, const char *word) {
  assert(self != NULL);
  assert(word != NULL);

  // Vérifier la capacité du tableau
  if(self->capacity == self->size) {
    word_array_grow(self);
  }

  // Ajouter le nouveau mot au tableau
  self->data[self->size] = string_duplicate(word);
  self->size += 1;
}

void word_array_search_anagrams(const struct word_array *self, const char *word, struct word_array *result) {
  assert(self != NULL);
  assert(word != NULL);
  assert(result != NULL);

  // Comparer word avec tous les éléments du tableau
  for(size_t i = 0; i < self->size; ++i) {
    if(string_are_anagrams(self->data[i], word)) {
      // Ajouter l'anagramme au tableau resultat
      word_array_add(result, self->data[i]);
    }
  }
}

/*
 * Échanger deux valeurs aux indidces i et j dans un tableau
 */
static void word_array_swap(struct word_array *self, size_t i, size_t j) {
  assert(self != NULL);
  assert(i < self->size);
  assert(j < self->size);

  char *tmp = self->data[i];
  self->data[i] = self->data[j];
  self->data[j] = tmp;
}

/*
 * Trouver le pivot d'un tableau de mots et placer les éléments correctement
 */
static size_t word_array_quick_sort_partition(struct word_array *self, size_t low, size_t high) {
  assert(self != NULL);
  assert(low < self->size);
  assert(high < self->size);

  // Trouver le pivot
  size_t pivot_index = (low + high)/2;
  const char *pivot_value = self->data[pivot_index];

  // Placer les éléments correctement selont le pivot
  word_array_swap(self, pivot_index, high);
  size_t current = low;
  for(size_t i = low; i < high; ++i) {
    if(strcmp(pivot_value, self->data[i]) > 0) {
      word_array_swap(self, i, current);
      ++current;
    }
  }

  // Placer le pivot au bon endroit
  word_array_swap(self, high, current);

  return current;
}

/*
 * Trier un tableau de mots avec QuickSort
 */
static void word_array_quick_sort(struct word_array *self, ptrdiff_t low, ptrdiff_t high) {
  assert(self != NULL);
  assert(low <= self->size);
  assert(high <= self->size);

  if(low < high) {
    // Trouver le pivot
    size_t pivot = word_array_quick_sort_partition(self, low, high);
    // Trier récursivement avant et après le pivot
    word_array_quick_sort(self, low, pivot - 1);
    word_array_quick_sort(self, pivot + 1, high);
  }
}

void word_array_sort(struct word_array *self) {
  assert(self != NULL);

  // Trier avec QuickSort
  word_array_quick_sort(self, 0, self->size - 1);
}

void word_array_print(const struct word_array *self) {
  assert(self != NULL);

  // Parcourir l'ensemble des éléments du tableau
  for(size_t i = 0; i < self->size; ++i) {
    printf("%s\n", self->data[i]);
  }
}

void word_array_read_file(struct word_array *self, const char *filename) {
  // Buffer du mot à lire
  char word[WORD_LETTERS_MAX];

  // Ouvrir le fichier à lire
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    fprintf(stderr, "Error when opening file '%s'\n", filename);
    return;
  }

  // Parcourir l'ensemble du fichier
  while(!feof(fp)) {
    fgets(word, WORD_LETTERS_MAX, fp);
    clean_newline(word, WORD_LETTERS_MAX);
    word_array_add(self, word);
  }

  fclose(fp);
}

/* 
 * ----------------------------------------
 * -> Partie 3 : Dictionnary
 * ----------------------------------------
 */

void word_dict_bucket_destroy(struct word_dict_bucket *bucket) {
  if(bucket != NULL) {
    // Détruire le noeud suivant
    word_dict_bucket_destroy(bucket->next);
    // Détruire le noeud courant
    free(bucket);
  }
}

struct word_dict_bucket *word_dict_bucket_add(struct word_dict_bucket *bucket, const char *word) {
  // Allocation de la mémoire du nouveau noeud
  struct word_dict_bucket *new_node = malloc(sizeof(struct word_dict_bucket));
  new_node->word = word;

  // Vérifier si la liste est vide
  if(bucket == NULL) {
    new_node->next = NULL;
    bucket = new_node;

    return bucket;
  }

  // Ajout du noeud
  new_node->next = bucket;
  bucket = new_node;

  return bucket;
}

void word_dict_create(struct word_dict *self) {
  self->size = 10;
  self->buckets = calloc(self->size, sizeof(struct word_dict_bucket*));
  for(size_t i = 0; i < self->size; ++i) {
    self->buckets[i] = NULL;
  }
  self->count = 0;
}

void word_dict_destroy(struct word_dict *self) {
  assert(self != NULL);

  for(size_t i = 0; i < self->size; ++i) {
    word_dict_bucket_destroy(self->buckets[i]);
  }
  free(self->buckets);
  self->size = 0;
  self->count = 0;
}

size_t fnv_hash(const char *key) {
  assert(key != NULL);

  // Dupliquer et trier la clé
  char *dup_key = string_duplicate(key);
  string_sort_letters(dup_key);

  // FNV-1a hash
  const size_t key_size = strlen(dup_key);
  size_t hash = FNV_OFFSET_BASIS;
  for(size_t i = 0; i < key_size; ++i) {
    hash = hash ^ dup_key[i];
    hash = hash * FNV_PRIME;
  }

  free(dup_key);

  return hash;
}

void word_dict_rehash(struct word_dict *self) {
  assert(self != NULL);

  // Doubler la taille du tableau
  size_t size = self->size * 2;
  struct word_dict_bucket **buckets = calloc(size, sizeof(struct word_dict_bucket));
  for(size_t i = 0; i < size; ++i) {
    buckets[i] = NULL;
  }

  // Recalculer les indices des éléments
  for(size_t i = 0; i < self->size; ++i) {
    struct word_dict_bucket *current = self->buckets[i];
    while(current != NULL) {
      // Obtenir le nouvel indice
      size_t new_index = fnv_hash(current->word) % size;
      // Déplacer le noued dans la nouvel liste
      struct word_dict_bucket *tmp = current;
      current = current->next;
      tmp->next = buckets[new_index];
      buckets[new_index] = tmp;
    }
  }

  // Insérer les nouvelles valeurs dans la structure
  self->size = size;
  free(self->buckets);
  self->buckets = buckets;
}

void word_dict_add(struct word_dict *self, const char *word) {
  assert(self != NULL);
  assert(word != NULL);

  // Effectuer un rehash si nécessaire
  if(self->count / self->size >= 0.5) {
    word_dict_rehash(self);
  }

  // Ajouter un nouvel élément au dictionnaire
  size_t index = fnv_hash(word) % self->size;
  self->buckets[index] = word_dict_bucket_add(self->buckets[index], word);
}

void word_dict_fill_with_array(struct word_dict *self, const struct word_array *array) {
  assert(self != NULL);
  assert(array != NULL);

  for(size_t i = 0; i < array->size; ++i) {
    word_dict_add(self, array->data[i]);
  }
}

void word_dict_search_anagrams(const struct word_dict *self, const char *word, struct word_array *result) {
  // Parcourir le dictionnaire
  for(size_t i = 0; i < self->size; ++i) {
    struct word_dict_bucket *current = self->buckets[i];
    while(current != NULL) {
      // Vérifier si le mot courant est un anagramme de word
      if(string_are_anagrams(current->word, word)) {
        // Ajouter le mot au tableau de mots
        word_array_add(result, current->word);
      }
      current = current->next;
    }
  }
}

/* 
 * ----------------------------------------
 * -> Partie 4 : Wildcards
 * ----------------------------------------
 */

void wildcard_create(struct wildcard *self) {
}

void wildcard_search(struct wildcard *self, const char *word) {
}

void word_array_search_anagrams_wildcard(const struct word_array *self, const char *word, struct word_array *result) {
}

void word_dict_search_anagrams_wildcard(const struct word_dict *self, const char *word, struct word_array *result) {
}
