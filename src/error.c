/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 22:36:42 by vbleskin          #+#    #+#             */
/*   Updated: 2026/01/05 00:49:45 by vbleskin         ###   ########.fr       */
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
 * Fonction pour free un tableau de chaine de caracteres.
 */
void	*free_tab(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
	return (NULL);
}

/**
 * Fonction pour fermer tous les file descriptors ouverts durant pipex.
 */
void	ft_close_all_fds(t_data *data)
{
	int	count;

	count = 0;
	while (count < 2 * (data->n_cmds - 1))
	{
		close(data->pipefds[count]);
		count++;
	}
	if (data->fd_in != FAIL)
		close(data->fd_in);
	if (data->fd_out != FAIL)
		close(data->fd_out);
}
