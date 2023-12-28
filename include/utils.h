#ifndef UTILS_H
#define UTILS_H

void make_frequency_vectors(char* text, int* counts, char** all_tokens, char** sentence_tokens);
double cosine(char* s1, char* s2);
int equals(char* s1, char* s2);
void split(char* str, char** list);
char*  trim(char* str, int end);
void   copy(const char* s, char* d);


#endif
