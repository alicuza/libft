# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/16 23:38:42 by sancuta           #+#    #+#              #
#    Updated: 2026/11/04 17:21:17 by sancuta          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---- project ------------------------------------------------------------- #
NAME	= libft.a

# ---- compiler / linker --------------------------------------------------- #
CC				?= cc
CFLAGS			?= -MMD -MP -Wall -Wextra -Werror
AR				= ar
ARFLAGS			= -rcs
RM				= rm
RMFLAGS			= -rf

# ---- build flags --------------------------------------------------------- #
RELEASE_FLAGS	?= -O2
DEBUG_FLAGS		?= -O0 -g3 -DDEBUG

# ---- make ---------------------------------------------------------------- #
ifeq ($(filter -j% --jobs%,$(MAKEFLAGS)),)
MAKEFLAGS += -j$(shell nproc 2>/dev/null || echo 1)
endif

# ---- sanitizer ----------------------------------------------------------- #
ifdef SAN
CFLAGS += -fsanitize=address
endif

# ---- build directories --------------------------------------------------- #
PRINTF_DIR		= printf
GNL_DIR			= gnl
ARENA_DIR		= arena
BUILD_DIR		= build
RELEASE_DIR		= $(BUILD_DIR)/release
DEBUG_DIR		= $(BUILD_DIR)/debug
RELEASE_NAME	= $(RELEASE_DIR)/$(NAME)
DEBUG_NAME		= $(DEBUG_DIR)/$(NAME)

# ---- sources ------------------------------------------------------------- #
SRCS = \
		ft_isalpha.c \
		ft_issign.c \
		ft_isspace.c \
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
		ft_indchr.c \
		ft_strncmp.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strnstr.c \
		ft_atoi.c \
		ft_atol.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_print_memory.c \
		ft_write.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstadd_back.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c \
		handle_exit.c \
		sig_digits_strlen.c \
		$(PRINTF_DIR)/ft_get_form_spec.c \
		$(PRINTF_DIR)/ft_printf.c \
		$(PRINTF_DIR)/ft_printf_padding.c \
		$(PRINTF_DIR)/ft_printf_utils.c \
		$(PRINTF_DIR)/ft_print_handler.c \
		$(PRINTF_DIR)/ft_prt_hex.c \
		$(PRINTF_DIR)/ft_prt_int.c \
		$(PRINTF_DIR)/ft_prt_uint.c \
		$(PRINTF_DIR)/ft_put_nbr_base.c \
		$(GNL_DIR)/get_next_line.c \
		$(GNL_DIR)/get_next_line_utils.c \
		$(ARENA_DIR)/arena_alloc_reset.c \
		$(ARENA_DIR)/arena_init_free.c \
		$(ARENA_DIR)/arena_save_restore.c \
		$(ARENA_DIR)/arena_strings.c \
		$(ARENA_DIR)/arena_itoa.c \
		$(ARENA_DIR)/arena_split.c \
		$(ARENA_DIR)/arena_pointer.c \
		$(ARENA_DIR)/arena_cleanup.c

# ---- objects / dependencies ---------------------------------------------- #
OBJS		= $(addprefix $(RELEASE_DIR)/, $(SRCS:.c=.o))
DEBUG_OBJS	= $(addprefix $(DEBUG_DIR)/, $(SRCS:.c=.o))
DEPS		= $(OBJS:.o=.d) $(DEBUG_OBJS:.o=.d)

# ---- targets ------------------------------------------------------------- #
all: $(RELEASE_NAME)

asan:
	$(MAKE) debug SAN=1

debug: $(DEBUG_NAME)

$(RELEASE_NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(DEBUG_NAME): $(DEBUG_OBJS)
	$(AR) $(ARFLAGS) $@ $^

# ---- object compilation -------------------------------------------------- #
$(RELEASE_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(RELEASE_FLAGS) -c $< -o $@

$(DEBUG_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -c $< -o $@

# ---- utility targets ----------------------------------------------------- #
clean:
	$(RM) $(RMFLAGS) $(OBJS) $(DEBUG_OBJS) $(DEPS)

fclean:
	$(MAKE) clean
	$(RM) $(RMFLAGS) $(BUILD_DIR)

re:
	$(MAKE) fclean
	$(MAKE) all

# ---- phony targets ------------------------------------------------------- #
.PHONY: all clean fclean re debug

# ---- dependencies -------------------------------------------------------- #
-include $(DEPS)
