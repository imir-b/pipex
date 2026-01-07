/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 22:36:42 by vbleskin          #+#    #+#             */
/*   Updated: 2026/01/07 10:54:39 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * Affiche le message d'erreur 's' sur STDERR (2) et return 1 pour code erreur.
 */
int	ft_error(char *s)
{
	ft_putendl_fd(s, STDERR_FILENO);
	return (ERROR);
}

/**
 * Appel strjoin pour creer un messasge d'erreur a partir de s1 et s2. 
 */
int	ft_error_strs(char *s1, char *s2)
{
	char	*msg;

	msg = ft_strjoin(s1, s2);
	if (!msg)
		return (ERROR);
	ft_error(msg);
	free(msg);
	return (SUCCESS);
}
