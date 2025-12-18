# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/14 21:18:51 by vbleskin          #+#    #+#              #
#    Updated: 2025/12/18 04:33:51 by vbleskin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex

SRC			= main.c utils.c
OBJ			=

CFLAGS		= -Wall -Werror -Wextra -I includes
RM			= rm -af

# rules
all :		$NAME

NAME :
			CC $CFLAGS