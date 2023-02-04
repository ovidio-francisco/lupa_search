#ifndef LUPA_H
#define LUPA_H

#define EXTENDED "âãäáàêẽëéèîĩïíìôõöóòûũüúùyŷỹÿýỳçℤÂÃÄÁÀÊẼËÉÈÎĨÏÍÌÔÕÖÓÒÛŨÜÚÙYŶỸŸÝỲÇ.,:;!@?-€"
#define REDUCED  "AAAAAEEEEEIIIIIOOOOOUUUUUIIIIIICZAAAAAEEEEEIIIIIOOOOOUUUUUIIIIIIC        E" 

void   init();
double lupa(char* s1, char* s2);
void   reduce(char* s, char* d);

void copy(const char* s, char* d, int count);

#endif
