#ifndef LUPA_H
#define LUPA_H

#define EXTENDED "âãäáàêẽëéèîĩïíìôõöóòûũüúùyŷỹÿýỳçℤÂÃÄÁÀÊẼËÉÈÎĨÏÍÌÔÕÖÓÒÛŨÜÚÙYŶỸŸÝỲÇ.,:;!@?-€"
#define REDUCED  "AAAAAEEEEEIIIIIOOOOOUUUUUIIIIIICZAAAAAEEEEEIIIIIOOOOOUUUUUIIIIIIC        E" 

char   init();
char   deinit();
double lupa(char* s1, char* s2);
char*  clear(char* s, char* d);
char   get_clean(char*s, int i, int* jmp);


#endif


