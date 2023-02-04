
#define test(condition, title) \
	((condition)) ? \
		( printf("%s was passed\n", title), 1) : \
		( printf("%s failed\n", title), 0) \


int test_clean(char* str, char* expected, char* msg);


