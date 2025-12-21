# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/14 21:18:51 by vbleskin          #+#    #+#              #
#    Updated: 2025/12/19 14:05:26 by vbleskin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex

SRC			= main.c utils.c
OBJ			=

SRC_DIR		= /src
OBJ_DIR		= /obj

CFLAGS		= -Wall -Werror -Wextra -I includes
RM			= rm -af

# rules
all :		$NAME

NAME :
			CC $CFLAGS