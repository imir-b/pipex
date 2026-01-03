/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 22:36:42 by vbleskin          #+#    #+#             */
/*   Updated: 2026/01/03 22:59:24 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_error(char *s)
{
	ft_putendl_fd(s, STDERR_FILENO);
	return (ERROR);
}

void	*free_tab(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
	return (NULL);
}

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
