#include <stdio.h>
#include <string.h>
#include <stdlib.h>

union u_data
{
	char string[8];
	int number;
};

int main(void)
{
	union u_data data;
	strcpy(data.string, "123");
	data.number = atoi(data.string);
	printf("%zd, %s, %d\n", sizeof(data), data.string, data.number);
}
