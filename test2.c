#include <stdio.h>

int main(void)
{
	printf("Ich bin der Anton aus Tirol!\n%80s\n", "hello everybody!");
	printf("Ich bin der Anton aus Tirol!\n%-80s\n", "hello everybody!");
	printf("%  s\n", "hello everybody!");
	return 0;
}
