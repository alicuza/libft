/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_libft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 00:25:08 by sancuta           #+#    #+#             */
/*   Updated: 2025/10/07 01:35:42 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include <stdio.h>
#include <bsd/string.h>

TestSuite(is_something_suite);

Test(is_something_suite, ft_isalpha)
{
	cr_expect(not(ft_isalpha(64)), "Expected ft_isalpha(64) == false");
	cr_expect(ft_isalpha(65), "Expected ft_isalpha(65) == true");
	cr_expect(ft_isalpha(90), "Expected ft_isalpha(90) == true");
	cr_expect(not(ft_isalpha(91)), "Expected ft_isalpha(91) == false");
	cr_expect(not(ft_isalpha(96)), "Expected ft_isalpha(96) == false");
	cr_expect(ft_isalpha(98), "Expected ft_isalpha(98) == true");
	cr_expect(ft_isalpha(122), "Expected ft_isalpha(122) == true");
	cr_expect(not(ft_isalpha(123)), "Expected ft_isalpha(123) == false");
}

Test(is_something_suite, ft_isdigit)
{
	cr_expect(not(ft_isdigit(47)), "Expected ft_isdigit(47) == false");
	cr_expect(ft_isdigit(48), "Expected ft_isdigit(48) == true");
	cr_expect(ft_isdigit(57), "Expected ft_isdigit(57) == true");
	cr_expect(not(ft_isdigit(58)), "Expected ft_isdigit(58) == false");
}

Test(is_something_suite, ft_isalnum)
{
	cr_expect(not(ft_isalnum(47)), "Expected ft_isalnum(47) == false");
	cr_expect(ft_isalnum(48), "Expected ft_isalnum(48) == true");
	cr_expect(ft_isalnum(57), "Expected ft_isalnum(57) == true");
	cr_expect(not(ft_isalnum(58)), "Expected ft_isalnum(58) == false");
	cr_expect(not(ft_isalnum(64)), "Expected ft_isalnum(64) == false");
	cr_expect(ft_isalnum(65), "Expected ft_isalnum(65) == true");
	cr_expect(ft_isalnum(90), "Expected ft_isalnum(90) == true");
	cr_expect(not(ft_isalnum(91)), "Expected ft_isalnum(91) == false");
	cr_expect(not(ft_isalnum(96)), "Expected ft_isalnum(96) == false");
	cr_expect(ft_isalnum(98), "Expected ft_isalnum(98) == true");
	cr_expect(ft_isalnum(122), "Expected ft_isalnum(122) == true");
	cr_expect(not(ft_isalnum(123)), "Expected ft_isalnum(123) == false");
}

Test(is_something_suite, ft_isascii)
{
	cr_expect(not(ft_isascii(-1)), "Expected ft_isascii(130) == false");
	cr_expect(ft_isascii(0), "Expected ft_isascii(20) == true");
	cr_expect(ft_isascii(127), "Expected ft_isascii(48) == true");
	cr_expect(not(ft_isascii(128)), "Expected ft_isascii(130) == false");
}

Test(is_something_suite, ft_isprint)
{
	cr_expect(not(ft_isprint(31)), "Expected ft_isprint(31) == false");
	cr_expect(ft_isprint(32), "Expected ft_isprint(32) == true");
	cr_expect(ft_isprint(126), "Expected ft_isprint(126) == true");
	cr_expect(not(ft_isprint(127)), "Expected ft_isprint(127) == false");
}

/*
typedef struct	s_string_cases
{
	void *input[];
	void *expected_output[];

}	t_string_cases;
 */

size_t	count_str_elements(char **array)
{
	size_t i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

size_t	count_int_elements(int *array)
{
	size_t	i;

	i = 0;
	while (array[i] != -1)
		i++;
	return (i);
}

TestSuite(string_suite);

typedef struct cr_mem	t_cr_mem;

typedef struct	s_str_input
{
	char	*str;	// string
	char	c;		// char
}	t_str_input;

//static t_str_input	data[50];
size_t				buffersize;
static char			*buffer1;
static char			*buffer2;
static size_t		str_len[50] = { 0 };
//static void		**ptr_array_input[50] = { NULL };
static char			*str_input[50] = { NULL }; // find better solution
static size_t		str_nr = 0;
static int			int_input[50] = { 0 };
static size_t		input_nr = 0;
static size_t		third_input[50] = { 0 };
static size_t		third_nr = 0;
//static char			*expected[50][50];
//size_t				expected_word_nr;
//static char			**actual[50];

/*	TODO: think of a better way to track the variables I am using.
	Might even be a better idea to have only one test function per file.
	Something to think about.
	Maybe I should look into unions and create groupings of parameters
	by their position as arguments.
	ex:
	union
	{
		int one;
		char one;
		char* one;
		char** one;

		int two;
		char two;
		char* two;
		char** two;
	}
*/
void	ft_strlen_setup(void)
{
	size_t	i;

	str_input[0] = "hello world";
	str_input[1] = "h";
	str_input[2] = "";
	str_input[3] = NULL; // test cases can be written before NULL
	input_nr = count_str_elements(str_input);
	i = 0;
	while (i < input_nr)
	{
		str_len[i] = strlen(str_input[i]);
		i++;
	}
}

void	ft_strlen_teardown(void)
{
	bzero(str_input, sizeof (str_input));
	bzero(str_len, sizeof(str_len));
	input_nr = 0;
}

Test(string_suite, ft_strlen, .init = ft_strlen_setup)
{
	size_t	i;

	i = 0;
	while (i < input_nr)
	{
		cr_expect(eq(sz, ft_strlen(str_input[i]), str_len[i]),
				"Expected ft_strlen(\"%s\") == %d",
				str_input[i], str_len[i]);
		i++;
	}
}

void	ft_memset_setup(void)
{
	int_input[0] = 32;
	int_input[1] = 46;
	int_input[2] = 48;
	/* ---> test cases can be written in here <--- */
	int_input[6] = -1;
	input_nr = sizeof (int_input) / sizeof (int);
	str_len[0] = 10;
	str_len[1] = 50;
	str_len[2] = 100;
	buffersize = 50;
	buffer1 = malloc(buffersize);
	buffer2 = malloc(buffersize);
	bzero(buffer1, buffersize);
	memset(buffer2, '1', buffersize);
}

void	ft_memset_teardown(void)
{
	free(buffer1);
	free(buffer2);
	buffer1 = NULL;
	buffer2 = NULL;
	buffersize = 0;
	bzero(int_input, sizeof(int_input));
	bzero(str_len, sizeof (str_len));
	input_nr = 0;
}

Test(string_suite, ft_memset, .init = ft_memset_setup, .fini = ft_memset_teardown)
{
	size_t	i;

	i = 0;
	while (i < input_nr)
	{
		ft_memset(buffer1, int_input[i], str_len[i]);
		memset(buffer2, int_input[i], str_len[i]);

		t_cr_mem buffer1_mem = { .data = buffer1, .size = str_len[i] };
		t_cr_mem buffer2_mem = { .data = buffer2, .size = str_len[i] };

		cr_expect(eq(mem, buffer1_mem, buffer2_mem),
				"For '%d' expected ft_memset == memset",
				int_input[i]);
		i++;
	}
}

void	ft_bzero_startup(void)
{
	str_len[0] = 10;
	str_len[1] = 50;
	input_nr = 2;
	buffersize = 50;
	buffer1 = malloc(50);
	buffer2 = malloc(50);
	memset(buffer1, 'a', buffersize);
	memset(buffer2, 'a', buffersize);
}

void	ft_bzero_teardown(void)
{
	free(buffer1);
	free(buffer2);
	buffer1 = NULL;
	buffer2 = NULL;
	buffersize = 0;
	bzero(str_len, sizeof (str_len));
	input_nr = 0;
}

Test(string_suite, ft_bzero, .init = ft_bzero_startup, .fini = ft_bzero_teardown)
{
	size_t	i;

	i = 0;
	while (i < input_nr)
	{
		ft_bzero(buffer1, str_len[i]);
		bzero(buffer2, str_len[i]);

		t_cr_mem buffer1_mem = { .data = buffer1, .size = str_len[i] };
		t_cr_mem buffer2_mem = { .data = buffer2, .size = str_len[i] };

		cr_expect(eq(mem, buffer1_mem, buffer2_mem),
				"Expected ft_bzero == bzero");
		i++;
	}
}

void	ft_memcpy_startup(void)
{
	str_input[0] = "hello world";
	str_input[1] = "h";
	str_input[2] = "";
	str_input[3] = NULL; // test cases can be written before NULL
	str_len[0] = 11;
	str_len[1] = 1;
	str_len[2] = 0;
	input_nr = count_str_elements(str_input);
	buffersize = 50;
	buffer1 = malloc(50);
	buffer2 = malloc(50);
	memset(buffer1, 'a', buffersize);
	memset(buffer2, '1', buffersize);
}

void	ft_memcpy_teardown(void)
{
	free(buffer1);
	free(buffer2);
	buffer1 = NULL;
	buffer2 = NULL;
	buffersize = 0;
	bzero(str_input, sizeof (str_input));
	bzero(str_len, sizeof (str_len));
	input_nr = 0;
}

Test(string_suite, ft_memcpy, .init = ft_memcpy_startup, .fini = ft_memcpy_teardown)
{
	size_t	i;

	i = 0;
	while (i < input_nr)
	{
		ft_memcpy(buffer1, str_input[i], str_len[i]);
		memcpy(buffer2, str_input[i], str_len[i]);

		t_cr_mem buffer1_mem = { .data = buffer1, .size = str_len[i] };
		t_cr_mem buffer2_mem = { .data = buffer2, .size = str_len[i] };

		cr_expect(eq(mem, buffer1_mem, buffer2_mem),
				"Expected ft_memcpy == memcpy");
		i++;
	}
}

void	ft_memmove_startup(void)
{
	str_input[0] = "hello world";
	str_input[1] = "h";
	str_input[2] = "";
	str_input[3] = NULL; // test cases can be written before NULL
	str_len[0] = 10;
	str_len[1] = 1;
	str_len[2] = 0;
	input_nr = count_str_elements(str_input);
	buffersize = 50;
	buffer1 = malloc(50);
	buffer2 = malloc(50);
	memset(buffer1, 'a', buffersize);
	memset(buffer2, '1', buffersize);
}

void	ft_memmove_teardown(void)
{
	free(buffer1);
	free(buffer2);
	buffer1 = NULL;
	buffer2 = NULL;
	buffersize = 0;
	bzero(str_input, sizeof (str_input));
	bzero(str_len, sizeof (str_len));
	input_nr = 0;
}

Test(string_suite, ft_memmove, .init = ft_memmove_startup, .fini = ft_memmove_teardown)
{
	size_t	i;

	i = 0;
	while (i < input_nr)
	{
		ft_memmove(buffer1, str_input[i], str_len[i]);
		memmove(buffer2, str_input[i], str_len[i]);

		t_cr_mem buffer1_mem = { .data = buffer1, .size = str_len[i] };
		t_cr_mem buffer2_mem = { .data = buffer2, .size = str_len[i] };

		cr_expect(eq(mem, buffer1_mem, buffer2_mem),
				"Expected ft_memmove == memmove");
		i++;
	}
}

void	ft_strlcpy_startup(void)
{
	str_input[0] = "hello world";
	str_input[1] = "h";
	str_input[2] = "";
	str_input[3] = "Hello World";
	str_input[4] = NULL; // test cases can be written before NULL
	str_len[0] = 12;
	str_len[1] = 2;
	str_len[2] = 1;
	str_len[3] = 0;
	input_nr = count_str_elements(str_input);
	buffersize = 50;
	buffer1 = malloc(50);
	buffer2 = malloc(50);
	memset(buffer1, 'a', buffersize);
	memset(buffer2, '1', buffersize);
}

/*	TODO: rename str_len to int_input, if they can be controlled separately in the tests.
*/

void	ft_strlcpy_teardown(void)
{
	free(buffer1);
	free(buffer2);
	buffer1 = NULL;
	buffer2 = NULL;
	buffersize = 0;
	bzero(str_input, sizeof (str_input));
	bzero(str_len, sizeof (str_len));
	input_nr = 0;
}

Test(string_suite, ft_strlcpy, .init = ft_strlcpy_startup, .fini = ft_strlcpy_teardown)
{
	size_t	i;

	i = 0;
	while (i < input_nr)
	{
		ft_strlcpy(buffer1, str_input[i], str_len[i]);
		strlcpy(buffer2, str_input[i], str_len[i]);
/*		cr_log_info("sz = %zu, buffer1 = %s, buffer2 = %s", i, buffer1, buffer2);
		cr_expect(eq(str, buffer1, buffer2),
				"Expected ft_strlcpy == strlcpy");
*/		t_cr_mem buffer1_mem = { .data = buffer1, .size = str_len[i] };
		t_cr_mem buffer2_mem = { .data = buffer2, .size = str_len[i] };

		cr_expect(eq(mem, buffer1_mem, buffer2_mem),
				"Expected ft_strlcpy == strlcpy");
		i++;
	}
}

void	ft_strlcat_startup(void)
{
	str_input[0] = "Hello World";
	str_input[1] = "H";
	str_input[2] = "hello world";
	str_input[3] = "h";
	str_input[4] = "";
	str_input[5] = NULL;
	str_len[0] = 17;
	str_len[1] = 7;
	str_len[2] = 12;
	str_len[3] = 2;
	str_len[4] = 0;
	input_nr = count_str_elements(str_input);
	buffersize = 20;
	buffer1 = malloc(20);
	buffer2 = malloc(20);
	ft_memset(buffer1, 0, buffersize);
	ft_memset(buffer2, 0, buffersize);
	ft_memset(buffer1, 'a', 5);
	ft_memset(buffer2, 'a', 5);
}

void	ft_strlcat_teardown(void)
{
	free(buffer1);
	free(buffer2);
	buffer1 = NULL;
	buffer2 = NULL;
	buffersize = 0;
	bzero(str_input, sizeof (str_input));
	bzero(str_len, sizeof (str_len));
	input_nr = 0;
}

Test(string_suite, ft_strlcat, .init = ft_strlcat_startup, .fini = ft_strlcat_teardown)
{
	size_t	i;

	i = 0;
	while (i < input_nr)
	{
		ft_strlcat(buffer1, str_input[i], str_len[i]);
		strlcat(buffer2, str_input[i], str_len[i]);

//		cr_log_info("sz = %zu, buffer1 = \"%s\", buffer2 = \"%s\"", i, buffer1, buffer2);
		t_cr_mem buffer1_mem = { .data = buffer1, .size = str_len[i] };
		t_cr_mem buffer2_mem = { .data = buffer2, .size = str_len[i] };

		cr_expect(eq(mem, buffer1_mem, buffer2_mem),
				"Expected ft_strlcat == strlcat");
		buffer1 = ft_memset(buffer1, 0, buffersize);
		buffer2 = ft_memset(buffer2, 0, buffersize);
		buffer1 = ft_memset(buffer1, 'a', 5);
		buffer2 = ft_memset(buffer2, 'a', 5);
		i++;
	}
}

TestSuite(to_something_suite);

void	ft_toupper_startup(void)
{
	int_input[0] = 64;
	int_input[1] = 65;
	int_input[2] = 90;
	int_input[3] = 91;
	int_input[4] = 122;
	int_input[5] = 123;
	int_input[6] = -1;
	input_nr = count_str_elements(str_input);
}

void	ft_toupper_teardown(void)
{
	bzero(int_input, sizeof (int_input));
	input_nr = 0;
}

Test(to_something_suite, ft_toupper, .init = ft_toupper_startup, .fini = ft_toupper_teardown)
{
	size_t	i;

	i = 0;
	while (i < input_nr)
	{
		cr_expect(eq(int, ft_toupper(int_input[i]), ft_toupper(int_input[i])),
				"Expected ft_toupper == toupper");
		i++;
	}
}

void	ft_tolower_startup(void)
{
	int_input[0] = 64;
	int_input[1] = 65;
	int_input[2] = 90;
	int_input[3] = 91;
	int_input[4] = 122;
	int_input[5] = 123;
	int_input[4] = -1;
	input_nr = count_str_elements(str_input);
}

void	ft_tolower_teardown(void)
{
	bzero(int_input, sizeof (int_input));
	input_nr = 0;
}

Test(to_something_suite, ft_tolower, .init = ft_tolower_startup, .fini = ft_tolower_teardown)
{
	size_t	i;

	i = 0;
	while (i < input_nr)
	{
		cr_expect(eq(int, ft_tolower(int_input[i]), ft_tolower(int_input[i])),
				"Expected ft_tolower == tolower");
		i++;
	}
}

void	ft_strchr_startup(void)
{
	str_input[0] = "hello world";
	str_input[1] = "h";
	str_input[2] = "";
	str_input[3] = "Hello World";
	str_input[4] = NULL;	// test cases can be written before NULL
	int_input[0] = 108;	// 'l'
	int_input[1] = 65;	// 'A'
	int_input[2] = 32;	// ''
	int_input[3] = 87;	// 'W'
	int_input[4] = -1;
	input_nr = count_str_elements(str_input);
}

void	ft_strchr_teardown(void)
{
	bzero(str_input, sizeof (str_input));
	bzero(int_input, sizeof (int_input));
	input_nr = 0;
}

Test(string_suite, ft_strchr, .init = ft_strchr_startup, .fini = ft_strchr_teardown)
{
	size_t	i;

	i = 0;
	while (i < input_nr)
	{
		char	*tmp1 = ft_strchr(str_input[i], int_input[i]);
		char	*tmp2 = strchr(str_input[i], int_input[i]);
/*		cr_log_info("sz = %zu from %zu: tmp1 = %p, tmp2 = %p", i, input_nr, tmp1, tmp2);
		if (tmp1 && tmp2)
			cr_log_info("sz = %zu from %zu: *tmp1 = %c, *tmp2 = %c", i, input_nr, *tmp1, *tmp2);
		else
			cr_log_info("sz = %zu from %zu: one or both pointers are NULL", i, input_nr);
*/		cr_expect(eq(ptr, tmp1, tmp2),
				"Expected ft_strchr == strchr");
		i++;
	}
}

void	ft_strrchr_startup(void)
{
	str_input[0] = "hello world";
	str_input[1] = "h";
	str_input[2] = "";
	str_input[3] = "Hello World";
	str_input[4] = NULL;	// test cases can be written before NULL
	int_input[0] = 108;	// 'l'
	int_input[1] = 65;	// 'A'
	int_input[2] = 32;	// ''
	int_input[3] = 87;	// 'W'
	int_input[4] = -1;
	input_nr = count_int_elements(int_input);
}

void	ft_strrchr_teardown(void)
{
	bzero(str_input, sizeof (str_input));
	bzero(int_input, sizeof (int_input));
	input_nr = 0;
}

Test(string_suite, ft_strrchr, .init = ft_strrchr_startup, .fini = ft_strrchr_teardown)
{
	size_t	i;

	i = 0;
	while (i < input_nr)
	{
		char	*tmp1 = ft_strrchr(str_input[i], int_input[i]);
		char	*tmp2 = strrchr(str_input[i], int_input[i]);
		cr_expect(eq(ptr, tmp1, tmp2),
				"Expected ft_strrchr == strrchr");
		i++;
	}
}

void	ft_strncmp_startup(void)
{
	str_input[0] = "hello world";
	str_input[1] = "h";
	str_input[2] = "";
	str_input[3] = "Hello World";
	str_input[4] = NULL;	// test cases can be written before NULL
	str_nr = count_str_elements(str_input);
	int_input[0] = 8;	// 'l'
	int_input[1] = 6;	// 'A'
	int_input[2] = 3;	// ''
	int_input[3] = 10;	// 'W'
	int_input[4] = -1;
	input_nr = count_int_elements(int_input);
}

/*	TODO: i could add another str_input variable, for when we have multiple strings.
	maybe it would make more sense to have an individual struct for each test
	or for specific test_suites, which might be a better way of organizing them:
	by DATA
*/

void	ft_strncmp_teardown(void)
{
	bzero(str_input, sizeof (str_input));
	bzero(int_input, sizeof (int_input));
	input_nr = 0;
	str_nr = 0;
}

Test(string_suite, ft_strncmp, .init = ft_strncmp_startup, .fini = ft_strncmp_teardown)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < input_nr)
	{
		j = 0;
		while (j < str_nr)
		{
			int	tmp1 = ft_strncmp(str_input[j], str_input[(j + 1) % input_nr], int_input[i]);
			int	tmp2 = strncmp(str_input[j], str_input[(j + 1) % input_nr], int_input[i]);
			cr_expect(eq(int, tmp1, tmp2),
					"Expected ft_strncmp == strncmp");
			j++;
		}
		i++;
	}
}

void	ft_memchr_startup(void)
{

	str_input[0] = "hello world";
	str_input[1] = "h";
	str_input[2] = "";
	str_input[3] = "Hello World";
	str_input[4] = "buf1";
	str_input[5] = "buf1";
	str_input[6] = NULL;	// test cases can be written before NULL
	str_nr = count_str_elements(str_input);
	int_input[0] = 108;	// 'l'
	int_input[1] = 65;	// 'A'
	int_input[2] = 32;	// ' '
	int_input[3] = 87;	// 'W'
	int_input[4] = -1;
	input_nr = count_int_elements(int_input);
	third_input[0] = 0;
	third_input[1] = 1;
	third_input[2] = 5;
	third_input[3] = 10;
	third_nr = 3;
}

/*	i don't think i like the sentinel value approach for int arrays.
	i just don't know atm how i would argue either way for using SIZE_MAX or 0.
	at least in this case, i know 0 is not useful, since i want to use it as an input.
*/

void	ft_memchr_teardown(void)
{
	bzero(str_input, sizeof (str_input));
	bzero(int_input, sizeof (int_input));
	input_nr = 0;
	str_nr = 0;
}

Test(string_suite, ft_memchr, .init = ft_memchr_startup, .fini = ft_memchr_teardown)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	while (i < input_nr)
	{
		j = 0;
		while (j < str_nr)
		{
			k = 0;
			while (k < third_nr)
			{
				void	*tmp1 = ft_memchr(str_input[j], int_input[i], third_input[k]);
				void	*tmp2 = memchr(str_input[j], int_input[i], third_input[k]);
				cr_expect(eq(ptr, tmp1, tmp2),
						"Expected ft_memchr == memchr");
				if (tmp1 && tmp2)
				    cr_expect(eq(chr, *(char *)tmp1, *(char *)tmp2),
							"Expected ft_memchr == memchr");
				else
					cr_fail("tmp1 or tmp2 are NULL for %d %zu %zu", i, j, k);
				k++;
			}
			j++;
		}
		i++;
	}
}


/*void	ft_split_startup(void)
{
	input_nr = count_elements()

	data[0].str = "t b c v";
	data[0].c = ' ';

	expected[0][0] = "a";
	expected[0][1] = "b";
	expected[0][2] = "c";
	expected[0][3] = "v";
	expected[0][4] = NULL;
	expected_word_nr = 4;
}

Test(string_suite, ft_split)
{
	size_t	i;
	size_t	j;

	i = 0;

	actual[0] = ft_split(data[0].str, data[0].c);
	cr_log_info("expected %s, got %s", expected[0][0], actual[0][0]);
	while (i < input_nr)
	{
		actual[i] = ft_split(data[i].str, data[i].c);
		j = 0;
		while (j < expected_word_nr)
		{
			cr_log_info("on \033[5;31mword %zu\033[25;39m: expected %s, got %s", j, expected[i][j], actual[i][j]);
			cr_expect(eq(str, actual[i][j], expected[i][j]), "on \033[5;31mword %zu\033[25;39m: expected %s, got %s", j, expected[i][j], actual[i][j]);
			j++;
		}
		i++;
	}
}
*/
