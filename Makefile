NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
DFLAGS = -g
AFLAGS = rcs
CRITFLAG = -lcriterion
SRCS =	ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_strlen.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strncmp.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strnstr.c \
		ft_atoi.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
#		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c
OBJS = $(SRCS:.c=.o)

ANY_SRCS = $(wildcard *.c)
ANY_OBJS = $(ANY_SRCS:.c=.o)
TEST_NAME = test_libft
TEST_SRC = $(TEST_NAME).c
TEST_OBJ = $(TEST_NAME).o

all: $(NAME)

$(NAME): $(OBJS)
		ar $(AFLAGS) $@ $^

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re: fclean all

debug: CFLAGS += $(DFLAGS)
debug: fclean all

any: $(ANY_OBJS)
		ar $(AFLAGS) $@ $^

test: $(TEST_NAME)

$(TEST_NAME): $(TEST_OBJ) $(NAME)
		$(CC) $(CFLAGS) $(CRITFLAG) $^ -o $@

tclean:
		rm -f $(TEST_NAME)
		rm -f $(TEST_OBJ)
