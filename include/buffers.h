#ifndef BUFFERS_H
#define BUFFERS_H

#include <stddef.h>

extern char** cosine_tokens;
extern char** cosine_sentence_tokens;
extern int*   cosine_counts1;
extern int*   cosine_counts2;

char init_cosine_buffers(size_t total_tokens_size);
char deinit_cosine_buffers();
void clear_cosine_buffers();

#endif

