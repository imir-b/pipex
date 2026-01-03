/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 18:28:50 by vbleskin          #+#    #+#             */
/*   Updated: 2025/12/19 19:20:46 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>

# define FD_MAX 1024

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

//
// ------ UTILS ------
//

/**
 * Original ft_strlen de libft sans le segfault.
 */
size_t	ft_gnl_strlen(const char *str);
/**
 * Original ft_strchr de libft sans le segfault.
 */
char	*ft_gnl_strchr(const char *s, int c);
/**
 * Reproduit le comportement de concatenation de ft_strjoin mais free 's1'.
 */
char	*ft_gnl_realloc(char *s1, char *s2);

//
// ------ PROCESS ------
//

/**
 * Lis le fichier 'fd' dans 'stash' et met 'end' a 1 si fin du fichier ou -
 * -1 si erreur,
 * int fd : file descriptor,
 * char *stash : variable dans laquelle on met ce qu'on lit,
 * int *end : pointeur vers un int pour gerer la fin de fichier et les erreurs.
 */
char	*ft_add_to_stash(int fd, char *stash, int *end);
/**
 * Nettoie la variable static 'stash' pour garder uniquement ce qu'il y a -
 * apres le '\n',
 * - char **stash : pointeur vers la variable static avant nettoyage,
 * - ret : la variable static nettoyee.
 */
char	*ft_clean_stash(char **stash);

/**
 * Renvoie la prochaine ligne lue dans le file descriptor 'fd' ou -
 * NULL si fin de fichier,
 * - int fd : file descriptor,
 * - ret : la ligne finie par '\n' ou la derniere ligne ou NULL.
 */
char	*get_next_line(int fd);

#endif
