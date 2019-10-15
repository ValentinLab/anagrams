#include "anagrammes.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Part 1

bool string_are_anagrams(const char *str1, const char *str2) {
  return false;
}

char *string_duplicate(const char *str) {
  return NULL;
}

void string_sort_letters(char *str) {
}

void clean_newline(char *buf, size_t size) {
}

// Part 2

void word_array_create(struct word_array *self) {
}

void word_array_destroy(struct word_array *self) {
}

void word_array_add(struct word_array *self, const char *word) {
}

void word_array_search_anagrams(const struct word_array *self, const char *word, struct word_array *result) {
}

void word_array_sort(struct word_array *self) {
}

void word_array_print(const struct word_array *self) {
}

void word_array_read_file(struct word_array *self, const char *filename) {
  char word[WORD_LETTERS_MAX];

  FILE *fp = fopen(filename, "r");

  if (fp == NULL) {
    fprintf(stderr, "Error when opening file '%s'\n", filename);
    return;
  }

  while (!feof(fp)) {
    fgets(word, WORD_LETTERS_MAX, fp);
    clean_newline(word, WORD_LETTERS_MAX);
    word_array_add(self, word);
  }

  fclose(fp);
}

// Part 3

void word_dict_bucket_destroy(struct word_dict_bucket *bucket) {
}

struct word_dict_bucket *word_dict_bucket_add(struct word_dict_bucket *bucket, const char *word) {
  return NULL;
}


void word_dict_create(struct word_dict *self) {
}

void word_dict_destroy(struct word_dict *self) {
}

size_t fnv_hash(const char *key) {
  return 0;
}

void word_dict_rehash(struct word_dict *self) {
}

void word_dict_add(struct word_dict *self, const char *word) {
}

void word_dict_fill_with_array(struct word_dict *self, const struct word_array *array) {
}

void word_dict_search_anagrams(const struct word_dict *self, const char *word, struct word_array *result) {
}

// Part 4

void wildcard_create(struct wildcard *self) {
}

void wildcard_search(struct wildcard *self, const char *word) {
}

void word_array_search_anagrams_wildcard(const struct word_array *self, const char *word, struct word_array *result) {
}

void word_dict_search_anagrams_wildcard(const struct word_dict *self, const char *word, struct word_array *result) {
}
