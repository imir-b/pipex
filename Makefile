# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/14 21:18:51 by vbleskin          #+#    #+#              #
#    Updated: 2026/01/02 10:23:37 by vbleskin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NAME

NAME			=	pipex

# DEF

CC				= cc
CFLAGS			= -Wall -Werror -Wextra -I includes -I $(LIBFT_DIR)includes -g3
RM				= rm -rf

# DIR

SRC_DIR			=	src/
OBJ_DIR			=	obj/
LIBFT_DIR			=	$(SRC_DIR)libft/

# FILES

SRC_FILES		=	main.c utils.c error.c process.c parsing.c
SRCS			=	$(addprefix $(SRC_DIR), $(SRC_FILES))
OBJS			=	$(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))
LIBS			=	-L$(LIBFT_DIR) -lft

# RULES

all :			$(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
				@mkdir -p $(dir $@)
				$(CC) $(CFLAGS) -c $< -o $@

$(NAME) :		$(OBJS)
				@make -C $(LIBFT_DIR)
				$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

clean :
				@make clean -C $(LIBFT_DIR)
				$(RM) $(OBJ_DIR)

fclean :		clean
				@make fclean -C $(LIBFT_DIR)
				$(RM) $(NAME)

re :			fclean all

.PHONY:			all clean fclean re