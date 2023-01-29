
#define test(condition, title) \
	((condition)) ? \
		( printf("%s was passed\n", title), 1) : \
		( printf("%s failed\n", title), 0) \


#define test_clean(str, expected) \
	char test_clean_result[strlen(original)]; \
	clean(original, test_clean_result); \
	printf("Original  = %s\n", original); \
	printf("Result    = %s\n", test_clean_result); \
	printf("Expected  = %s\n", expected); \
	(strcmp(test_clean_result, expected) == 0) ? \
		( printf("that is what we expect\n"), 1) : \
		( printf("You disappointed me\n"), 0) \


