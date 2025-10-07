# `test_libft.c`
## general thoughts
- ex: even though `strlcat` has some safety concerns and uses defensive design (good wording?)
	in some cases, it does not check for some of the concerns I have been confronted by lately
	in discussions with colleagues: it does not check whether the input char * are not `NULL`.
	i have been considering adding checks to handle `NULL` pointers to the following functions.
## `ft_split`
- should i handle the input string being `NULL`? possibilities:
	0. keep behaviour undefinded, in line with the libc functions.
	1. return `NULL`:
		`if (!s) return = (NULL);`
	2. default to handling it as an empty string:
		`word_nr = 0; if (s) word_nr = count_words(s, c);`
- look into setup and teardown functions to dynamically allocate the size of
	the array of expected substrings, so we can handle arbitrarilly large numbers of words.
- look into generating the mix of different types of strings and delimiters from a sets.
- look into testing using control (non-printable) characters in the string and in the delim.
## `ft_substr`
- should i handle the index starting at the end of the input string? possibilities:
	0. keep behaviour undefinded, in line with the libc functions.
	1. return `NULL`:
		`if ((size_t)start >= len) return (NULL);`
	2. return an empty string:
		`sub = ""`
## `ft_strjoin`
- should i handle one of the input strings being `NULL`? possibilities:
	0. keep behaviour undefinded, in line with the libc functions.
	1. return `NULL`:
		`if (!s1 || !s2) return (NULL);`
	2. if only one of the input strings is `NULL`, we could return the other as is:
		`if (!s1 || !s2) if (s1) return (s1); else if (s2) return (s2); else return (NULL);`
## `ft_strtrim`
- should i handle the input string or set being `NULL`? possibilities:
	0. keep behaviour undefinded, in line with the libc functions.
	1. `if (!s1 || !set) return (NULL);`
	2. `if (!s1 || !set) if (s1) return (s1); else return (NULL);`
		if only the set is `NULL`, we could return the input string as is.

