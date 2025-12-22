/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 22:34:28 by vbleskin          #+#    #+#             */
/*   Updated: 2025/12/22 22:36:13 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*free_data(t_data *data)
{
	if (data->pipes)
	{
		free(data->pipes);
		data->pipes = NULL;
	}
	if (data->pids)
	{
		free(data->pids);
		data->pids = NULL;
	}
	if (data)
	{
		free(data);
		data = NULL;
	}
	if (data->fd_in)
		close(data->fd_in);
	if (data->fd_out)
		close(data->fd_out);
	return (NULL);
}

t_data	*ft_init_data(int ac, char **av)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (NULL);
	data->n_cmds = ac - 3;
	data->pipes = malloc(sizeof(int) * 2 * (data->n_cmds - 1));
	if (!data->pipes)
		return (free_data(data));
	data->pids = malloc(sizeof(pid_t) * data->n_cmds);
	if (!data->pids)
		return (free_data(data));
	data->fd_in = open(av[1], O_RDONLY);
	data->fd_out = open(av[ac], O_RDWR);
	if (data->fd_in == FAIL || data->fd_out == FAIL)
		return (free_data(data));
	return (data);
}
