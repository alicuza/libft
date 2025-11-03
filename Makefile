# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/16 23:38:42 by sancuta           #+#    #+#              #
#    Updated: 2025/10/27 12:13:40 by sancuta          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT = ./libft/libft.a
NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
AFLAGS = -rcs
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
		ar $(AFLAGS) $@ $?

$(LIBFT):
		make all -C libft
		cp $(LIBFT) $(NAME)

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		make clean -C libft
		rm -f $(OBJS)

fclean: clean
		make fclean -C libft
		rm -f $(NAME)
		rm -f .bonus

re: fclean all

bonus: .bonus

.bonus: $(OBJS)
		ar $(AFLAGS) $(NAME) $?
		touch .bonus

.PHONY: all clean fclean re bonus
