#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "get_next_line.h"

int	main(void)
{
	int fd = open("input_big.txt", O_RDONLY);
	if (fd == -1)
		return(printf("couldn't read file"), 1);
	char *next_line = get_next_line(fd);
	int i = 0;
	while(next_line)
	{
		printf("%d: %s\n", i, next_line);
		i++;
		free(next_line);
		next_line = get_next_line(fd);
	}
}
