#include <stdio.h>

int main(void)
{
	printf("%10.0s\n", "hello");
	printf("%20p\n", "hello");
	printf("%-20p\n", "hello");
	printf("%020p\n", "hello");
	printf("%-020p\n", "hello");
	printf("%20.0d\n", 1);
	printf("%020d\n", -2);
	printf("%30.20d\n", -2);
/*
	printf("%0#10x\n", 42);
	printf("%0#.10x\n", 42);
	printf("%#20x\n", 42);
	printf("%#20.10x\n", 42);
	printf("%0+12d\n", 138098);
	printf("%0+12d\n", -138098);
	printf("%+.12d\n", 138098);
	printf("%+.12d\n", -138098);
	printf("%+20.12d\n", 138098);
	printf("%+20.12d\n", -138098);
	printf("\n");

	printf("%+020d\n", 42);
	printf("%+.20d\n", 42);
*/
	return 0;
}
