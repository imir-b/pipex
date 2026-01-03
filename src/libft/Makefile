# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/04 15:11:54 by vbleskin          #+#    #+#              #
#    Updated: 2026/01/03 08:09:47 by vbleskin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NAME

NAME		=	libft.a


# DEF

CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra -I includes
RM			=	rm -rf
AR			=	ar -rcs


# DIR

SRC_DIR		=	src/
OBJ_DIR		=	obj/

CTYPE_DIR	=	ctype/
STR_DIR		=	string/
MEM_DIR		=	memory/
CONV_DIR	=	conversions/
IO_DIR		=	io/
LIST_DIR	=	list/
PRINTF_DIR	=	printf/
GNL_DIR		=	gnl/

# FILES

SRC_CTYPE	=	$(CTYPE_DIR)ft_isalnum.c $(CTYPE_DIR)ft_isalpha.c \
				$(CTYPE_DIR)ft_isascii.c $(CTYPE_DIR)ft_isdigit.c \
				$(CTYPE_DIR)ft_isprint.c $(CTYPE_DIR)ft_tolower.c \
				$(CTYPE_DIR)ft_toupper.c

SRC_STR		=	$(STR_DIR)ft_split.c $(STR_DIR)ft_strchr.c \
				$(STR_DIR)ft_strdup.c $(STR_DIR)ft_strndup.c \
				$(STR_DIR)ft_striteri.c $(STR_DIR)ft_strjoin.c \
				$(STR_DIR)ft_strlcat.c $(STR_DIR)ft_strlcpy.c \
				$(STR_DIR)ft_strlen.c $(STR_DIR)ft_strmapi.c \
				$(STR_DIR)ft_strncmp.c $(STR_DIR)ft_strnstr.c \
				$(STR_DIR)ft_strrchr.c $(STR_DIR)ft_strtrim.c \
				$(STR_DIR)ft_substr.c

SRC_MEM		=	$(MEM_DIR)ft_bzero.c $(MEM_DIR)ft_calloc.c \
				$(MEM_DIR)ft_memchr.c $(MEM_DIR)ft_memcmp.c \
				$(MEM_DIR)ft_memcpy.c $(MEM_DIR)ft_memmove.c \
				$(MEM_DIR)ft_memset.c

SRC_CONV	=	$(CONV_DIR)ft_atoi.c $(CONV_DIR)ft_itoa.c

SRC_IO		=	$(IO_DIR)ft_putchar_fd.c $(IO_DIR)ft_putendl_fd.c \
				$(IO_DIR)ft_putnbr_fd.c $(IO_DIR)ft_putstr_fd.c

SRC_LIST	=	$(LIST_DIR)ft_lstadd_back.c $(LIST_DIR)ft_lstadd_front.c \
				$(LIST_DIR)ft_lstclear.c $(LIST_DIR)ft_lstdelone.c \
				$(LIST_DIR)ft_lstiter.c $(LIST_DIR)ft_lstlast.c \
				$(LIST_DIR)ft_lstmap.c $(LIST_DIR)ft_lstnew.c \
				$(LIST_DIR)ft_lstsize.c

SRC_PRINTF	=	$(PRINTF_DIR)ft_printf.c $(PRINTF_DIR)printf_parsing.c \
				$(PRINTF_DIR)printf_parsing_flags.c \
				$(PRINTF_DIR)printf_handle_numbers.c \
				$(PRINTF_DIR)printf_handle_text.c \
				$(PRINTF_DIR)printf_utils_write.c \
				$(PRINTF_DIR)printf_utils_list.c \
				$(PRINTF_DIR)printf_utils_libft.c \
				$(PRINTF_DIR)printf_utils.c

SRC_GNL		=	$(GNL_DIR)get_next_line.c $(GNL_DIR)get_next_line_utils.c

SRC_FILES   =   $(SRC_CTYPE) $(SRC_STR) $(SRC_MEM) $(SRC_CONV) \
                $(SRC_IO) $(SRC_LIST) $(SRC_PRINTF) $(SRC_GNL)

SRCS		=	$(addprefix $(SRC_DIR), $(SRC_FILES))
OBJS		=	$(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))


# RULES

all:		$(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
			@mkdir -p $(dir $@)
			@$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS)
			@echo "$(NAME) compiled successfuly"
			@$(AR) $@ $^

clean:
			@$(RM) $(OBJ_DIR)
			@echo "$(NAME) cleaned successfuly"

fclean: 	clean
			@$(RM) $(NAME)

re: 		fclean all

.PHONY:		all clean fclean re