# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/11 22:29:22 by sancuta           #+#    #+#              #
#    Updated: 2025/12/14 05:34:20 by sancuta          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CC = cc
CFLAGS = -MMD -MP -Wall -Wextra -Werror
ARFLAGS = -rcs
SRCS =	ft_printf.c \
		ft_printf_utils.c \
		ft_printf_padding.c \
		ft_check_form_spec.c \
		ft_prt_int.c \
		ft_prt_uint.c \
		ft_prt_hex.c \
		ft_print_handler.c \
		ft_put_nbr_base.c \
		ft_get_form_spec.c
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

BSRCS =	ft_printf_bonus.c \
		ft_printf_utils_bonus.c \
		ft_printf_padding_bonus.c \
		ft_check_form_spec_bonus.c \
		ft_prt_int_bonus.c \
		ft_prt_uint_bonus.c \
		ft_prt_hex_bonus.c \
		ft_print_handler_bonus.c \
		ft_put_nbr_base_bonus.c \
		ft_get_form_spec_bonus.c
BOBJS = $(BSRCS:.c=.o)
BDEPS = $(BSRCS:.c=.d)

LIBFT_DIR = ./libft

all: libft_check $(NAME)

$(NAME): $(OBJS)
		cp $(LIBFT_DIR)/libft.a ./$(NAME)
		ar $(ARFLAGS) $@ $^

libft_check:
		make -C $(LIBFT_DIR)

clean:
		rm -f $(OBJS) $(BOBJS) $(DEPS) $(BDEPS) .bonus
		make -C $(LIBFT_DIR) clean

fclean: clean
		rm -f $(NAME)
		make -C $(LIBFT_DIR) fclean

re: fclean all

bonus: libft_check $(NAME) .bonus

.bonus: $(BOBJS)
		ar $(ARFLAGS) $(NAME) $^
		touch .bonus

.PHONY: all clean fclean re bonus libft_check

-include $(DEPS) $(BDEPS)
