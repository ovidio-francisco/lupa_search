#ifndef LUPA_H
#define LUPA_H

#define EXTENDED "âãäáàêẽëéèîĩïíìôõöóòûũüúùyŷỹÿýỳçℤÂÃÄÁÀÊẼËÉÈÎĨÏÍÌÔÕÖÓÒÛŨÜÚÙYŶỸŸÝỲÇ.,:;!@?-€"
#define REDUCED  "AAAAAEEEEEIIIIIOOOOOUUUUUIIIIII{ZAAAAAEEEEEIIIIIOOOOOUUUUUIIIIII{        E" 


#define _A 'A'
#define _B 'B'
#define _C 'C'
#define _D 'D'
#define _E 'E'
#define _F 'F'
#define _G 'G'
#define _H 'H'
#define _I 'I'
#define _J 'J'
#define _K 'K'
#define _L 'L'
#define _M 'M'
#define _N 'N'
#define _O 'O'
#define _P 'P'
#define _Q 'Q'
#define _R 'R'
#define _S 'S'
#define _T 'T'
#define _U 'U'
#define _V 'V'
#define _X 'X'
#define _Y 'Y'
#define _W 'W'
#define _Z 'Z'
#define _Ç '{'
#define _NH '~'

#define SPACE ' '
#define UNKNONW 127

#define VOWEL     1
#define CONSONANT 2
#define NUMBER    3

#define CONSONANTS {_B, _C, _D, _F, _G, _H, _J, _K, _L, _M, _N, _P, _Q, _R, _S, _T, _V, _X, _Z}
#define VOWELS     {_A, _E, _I, _O, _U, _Y}
#define NUMBERS    {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'}


char   init();
char   init_valids();
char   init_chars_types();
char   deinit();
char   deinit_valids();
char   deinit_char_types();
double similarity(char* s1, char* s2);
char*  clear(char* s, char* d);
char   get_clean(char*s, int i, int* jmp);


char is_vowel(char c);
char is_consonant(char c);
char is_number(char c);

#endif


