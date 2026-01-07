/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 10:53:08 by vbleskin          #+#    #+#             */
/*   Updated: 2026/01/07 10:54:47 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
 * Fonction pour free propremment la structure 'data'.
 */
void	*free_data(t_data *data)
{
	if (data->path_list)
		free_tab(data->path_list);
	if (data->pipefds)
	{
		free(data->pipefds);
		data->pipefds = NULL;
	}
	if (data->pids)
	{
		free(data->pids);
		data->pids = NULL;
	}
	if (data->fd_in)
		close(data->fd_in);
	if (data->fd_out)
		close(data->fd_out);
	if (data)
	{
		free(data);
		data = NULL;
	}
	return (NULL);
}

/**
 * Fonction pour free proprement la structure 'cmd_data'.
 */
void	*free_cmd_data(t_cmd_data *cmd_data)
{
	if (cmd_data->path)
	{
		free(cmd_data->path);
		cmd_data->path = NULL;
	}
	if (cmd_data->cmd)
		free_tab(cmd_data->cmd);
	if (cmd_data)
	{
		free(cmd_data);
		cmd_data = NULL;
	}
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
