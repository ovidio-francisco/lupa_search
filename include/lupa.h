#ifndef LUPA_H
#define LUPA_H

#define EXTENDED "âãäáàêẽëéèîĩïíìôõöóòûũüúùyŷỹÿýỳçℤÂÃÄÁÀÊẼËÉÈÎĨÏÍÌÔÕÖÓÒÛŨÜÚÙYŶỸŸÝỲÇ.,:;!@?-€"
#define REDUCED  "AAAAAEEEEEIIIIIOOOOOUUUUUIIIIIICZAAAAAEEEEEIIIIIOOOOOUUUUUIIIIIIC        E" 

void   init();
double lupa(char* s1, char* s2);
char*  clean(char* s, char* d);
char*  trim(char* str, int end);

void copy(const char* s, char* d, int count);

#endif


