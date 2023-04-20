#ifndef LUPA_H
#define LUPA_H

#define EXTENDED "âãäáàêẽëéèîĩïíìôõöóòûũüúùyŷỹÿýỳçℤÂÃÄÁÀÊẼËÉÈÎĨÏÍÌÔÕÖÓÒÛŨÜÚÙYŶỸŸÝỲÇ.,:;!@?-€"
#define REDUCED  "AAAAAEEEEEIIIIIOOOOOUUUUUIIIIIICZAAAAAEEEEEIIIIIOOOOOUUUUUIIIIIIC        E" 

void   init();
void   deinit();
double lupa(char* s1, char* s2);
char*  clean(char* s, char* d);


#endif


