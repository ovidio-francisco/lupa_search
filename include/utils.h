#ifndef UTILS_H
#define UTILS_H

double cosine(char* s1, char* s2);
void make_frequency_vetors(char* text, int* vec, char** l1);
int equals(char* s1, char* s2);
void split(char* str, char** list);
char*  trim(char* str, int end);
void   copy(const char* s, char* d);


#endif
