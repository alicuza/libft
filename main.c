#include "ft_printf.h"

int main(void)
{
	ft_printf("%+20.10d\n", 2);
	ft_printf("%20.10s\n", "hallo du hurenkind!");
	ft_printf("%-20.10s\n", "hallo du hurenkind!");
	return (0);
}
