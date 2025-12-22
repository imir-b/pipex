/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 21:21:00 by vbleskin          #+#    #+#             */
/*   Updated: 2025/12/22 22:43:53 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

void	ft_process_cmd(char *path, char **envp, char **cmd, t_data *data)
{
	if (dup2(data->fd_out, STDOUT_FILENO) == FAIL)
		return (perror("Error"), exit(ERROR));
	execve(path, cmd, envp);
}

void	ft_child_first()
{
	
}

void	ft_child_last()
{
	
}

void	ft_kill_zombies()
{
	
}

int	ft_create_pipes(t_data *data)
{
	int	n_pipes;

	n_pipes = 0;
	while (n_pipes < data->n_cmds - 1)
	{
		if (pipe(data->pipes + (2 * n_pipes)) == FAIL)
			return (perror("Error"), free_data(data), ERROR);
		n_pipes++;
	}
	return (n_pipes);
}

int	main(int ac, char **av, char **envp)
{
	const char	*path_line = ft_find_path(envp);
	char		**path_list;
	t_data		*data;

	if (!path_line || ac < 5)
		return (ft_error("Error: args or envp not valid"));
	data = ft_init_data;
	if (!ft_create_pipes(data))
		return (free_data(data), ft_error("Error: Failure creating pipes"));
	path_list = ft_split(path_line, ':');
	if (ft_parse_cmds(ac, av, envp, path_list))
		return (free_data(data), ft_error("Error: Parsing failed"));
	return (SUCCESS);
}
