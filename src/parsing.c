/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 22:34:28 by vbleskin          #+#    #+#             */
/*   Updated: 2025/12/24 05:37:02 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_find_path(char **envp)
{
	const char	*path = "PATH=";

	while (*envp)
	{
		if (!ft_strncmp(*envp, path, 5))
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}

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

t_data	*ft_init_data(int ac, char **av, const char *path_line)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (NULL);
	data->path_list = ft_split(path_line, ':');
	if (!data->path_list)
		return (free_data(data));
	data->n_cmds = ac - 3;
	data->pipefds = malloc(sizeof(int) * 2 * (data->n_cmds - 1));
	if (!data->pipefds)
		return (free_data(data));
	data->pids = malloc(sizeof(pid_t) * data->n_cmds);
	if (!data->pids)
		return (free_data(data));
	data->fd_in = open(av[1], O_RDONLY);
	if (data->fd_in == FAIL)
		return (perror(av[1]), free_data(data));
	data->fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->fd_out == FAIL)
		return (perror(av[ac - 1]), free_data(data));
	return (data);
}

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

t_cmd_data	*ft_init_cmd_data(char *cmd_line, char **path_list)
{
	t_cmd_data	*cmd_data;
	int			cur;

	cmd_data = ft_calloc(1, sizeof(t_cmd_data));
	if (!cmd_data)
		return (NULL);
	cmd_data->cmd = ft_split(cmd_line, ' ');
	if (!cmd_data->cmd)
		return (free_cmd_data(cmd_data));
	cur = 0;
	while (path_list[cur])
	{
		cmd_data->path = ft_super_join(path_list[cur], cmd_data->cmd[0], '/');
		if (!cmd_data->path)
			return (free_cmd_data(cmd_data));
		if (access(cmd_data->path, X_OK) == 0)
			return (cmd_data);
		else
			free(cmd_data->path);
		cur++;
	}
	return (free_cmd_data(cmd_data));
}
