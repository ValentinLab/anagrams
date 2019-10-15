#ifndef ANAGRAMMES_H
#define ANAGRAMMES_H

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// Part 1

bool string_are_anagrams(const char *str1, const char *str2);
char *string_duplicate(const char *str);
void string_sort_letters(char *str);
void clean_newline(char *buf, size_t size);

// Part 2

struct word_array {
  char **data;
  size_t size;
  size_t capacity;
};

void word_array_create(struct word_array *self);
void word_array_destroy(struct word_array *self);
void word_array_add(struct word_array *self, const char *word);
void word_array_search_anagrams(const struct word_array *self, const char *word, struct word_array *result);
void word_array_sort(struct word_array *self);
void word_array_print(const struct word_array *self);

#define WORD_LETTERS_MAX 32

void word_array_read_file(struct word_array *self, const char *filename);

// Part 3

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

// Part 4

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
