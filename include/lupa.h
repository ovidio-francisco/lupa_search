#ifndef LUPA_H
#define LUPA_H

#define ACCENTEDS "âãäáàêẽëéèîĩïíìôõöóòûũüúùyŷỹÿýỳçℤÂÃÄÁÀÊẼËÉÈÎĨÏÍÌÔÕÖÓÒÛŨÜÚÙYŶỸŸÝỲÇ.,:;!@?-€";
#define UNACCENTEDS "AAAAAEEEEEIIIIIOOOOOUUUUUIIIIIICZAAAAAEEEEEIIIIIOOOOOUUUUUIIIIIIC        E"; 

void   init();
double lupa(char* s1, char* s2);
void   clean(char* s, char* d);

void copy(const char* s, char* d, int count);

/* int chain2(unsigned char c1, unsigned char c2);
 * int chain3(unsigned char c1, unsigned char c2, unsigned char c3);
 * 
 * char unchain(int i, int part); */

#endif
