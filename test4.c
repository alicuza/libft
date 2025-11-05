#include <stdio.h>

int main(void)
{
	printf("hello % 010#d boys", 2);
/*
	printf("%\n");

	int n = 2;
	printf("%#lx\n", &n);
	printf("%p\n", &n);

	printf("%-5.2s\n", "h");
	printf("%-5.2s\n", "hello");
	printf("%5.2s\n", "h");
	printf("%5.2s\n", "hello");
	printf("%-5.8s\n", "h");
	printf("%-5.8s\n", "hello");
	printf("%5.8s\n", "h");
	printf("%5.8s\n", "hello");


	printf("%0 5d\n", 2);
	printf("%0 5d\n", -2);
	printf("%0+5d\n", 2);
	printf("%0+5d\n", -2);
	printf("%-+d\n", -2);
	printf("%-+d\n", 2);
	printf("%- d\n", -2);
	printf("%- d\n", 2);
	printf("%0+d\n", -2);
	printf("%0+d\n", 2);
	printf("%0 d\n", -2);
	printf("%0 d\n", 2);
	printf("%+d\n", -2);
	printf("%+d\n", 2);
	printf("% d\n", -2);
	printf("% d\n", 2);

	printf("%-#+c\n", '5');
	printf("%-# c\n", '5');
	printf("%0#+c\n", '5');
	printf("%0# c\n", '5');
	printf("%-#+s\n", "5");
	printf("%-# s\n", "5");
	printf("%0#+s\n", "5");
	printf("%0# s\n", "5");
	printf("%-#+p\n", "5");
	printf("%-# p\n", "5");
	printf("%0#+p\n", "5");
	printf("%0# p\n", "5");
	printf("%-#+d\n", '5');
	printf("%-# d\n", '5');
	printf("%0#+d\n", '5');
	printf("%0# d\n", '5');
	printf("%-#+i\n", '5');
	printf("%-# i\n", '5');
	printf("%0#+i\n", '5');
	printf("%0# i\n", '5');
	printf("%-#+u\n", '5');
	printf("%-# u\n", '5');
	printf("%0#+u\n", '5');
	printf("%0# u\n", '5');
	printf("%-#+x\n", '5');
	printf("%-# x\n", '5');
	printf("%0#+x\n", '5');
	printf("%0# x\n", '5');
	printf("%-#+X\n", '5');
	printf("%-# X\n", '5');
	printf("%0#+X\n", '5');
	printf("%0# X\n", '5');
	printf("%%\n");

	printf("%-#+5c\n", '5');
	printf("%-# 5c\n", '5');
	printf("%0#+5c\n", '5');
	printf("%0# 5c\n", '5');
	printf("%-#+5s\n", "5");
	printf("%-# 5s\n", "5");
	printf("%0#+5s\n", "5");
	printf("%0# 5s\n", "5");
	printf("%-#+5p\n", "5");
	printf("%-# 5p\n", "5");
	printf("%0#+5p\n", "5");
	printf("%0# 5p\n", "5");
	printf("%-#+5d\n", '5');
	printf("%-# 5d\n", '5');
	printf("%0#+5d\n", '5');
	printf("%0# 5d\n", '5');
	printf("%-#+5i\n", '5');
	printf("%-# 5i\n", '5');
	printf("%0#+5i\n", '5');
	printf("%0# 5i\n", '5');
	printf("%-#+5u\n", '5');
	printf("%-# 5u\n", '5');
	printf("%0#+5u\n", '5');
	printf("%0# 5u\n", '5');
	printf("%-#+5x\n", '5');
	printf("%-# 5x\n", '5');
	printf("%0#+5x\n", '5');
	printf("%0# 5x\n", '5');
	printf("%-#+5X\n", '5');
	printf("%-# 5X\n", '5');
	printf("%0#+5X\n", '5');
	printf("%0# 5X\n", '5');
	printf("%%\n");

	printf("%-#+.5c\n", '5');
	printf("%-# .5c\n", '5');
	printf("%0#+.5c\n", '5');
	printf("%0# .5c\n", '5');
	printf("%-#+.5s\n", "5");
	printf("%-# .5s\n", "5");
	printf("%0#+.5s\n", "5");
	printf("%0# .5s\n", "5");
	printf("%-#+.5p\n", "5");
	printf("%-# .5p\n", "5");
	printf("%0#+.5p\n", "5");
	printf("%0# .5p\n", "5");
	printf("%-#+.5d\n", '5');
	printf("%-# .5d\n", '5');
	printf("%0#+.5d\n", '5');
	printf("%0# .5d\n", '5');
	printf("%-#+.5i\n", '5');
	printf("%-# .5i\n", '5');
	printf("%0#+.5i\n", '5');
	printf("%0# .5i\n", '5');
	printf("%-#+.5u\n", '5');
	printf("%-# .5u\n", '5');
	printf("%0#+.5u\n", '5');
	printf("%0# .5u\n", '5');
	printf("%-#+.5x\n", '5');
	printf("%-# .5x\n", '5');
	printf("%0#+.5x\n", '5');
	printf("%0# .5x\n", '5');
	printf("%-#+.5X\n", '5');
	printf("%-# .5X\n", '5');
	printf("%0#+.5X\n", '5');
	printf("%0# .5X\n", '5');
	printf("%%\n");

	printf("%20.10d\n", 2);
	printf("%020s\n", "hello"); // 0 funktioniert nicht mit strings
	printf("%-020d\n", 2); //  cannot use 0 with -
	printf("%-20d\n", 2);
	printf("%20d\n", 2);
	printf("1: %0 20d\n", -2);
	printf("1: %0 20d\n", 2);
	printf("1: %0 +20d\n", 2);
	printf("2: %020d\n", 2);
	printf("%20d\n", 2);
	printf("%20d\n", 2);
	printf("%-20.10d\n", 2);
	printf("%- 20.10d\n", 2);
	printf("%-+20.10d\n", 2);
	printf("%-20.10d\n", -2);
	printf("%x\n", 2);
	printf("%#x\n", 2);
	printf("%X\n", -2);
	printf("%#X\n", -2);
	
	return (0);
*/
}
