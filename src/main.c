/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 21:21:00 by vbleskin          #+#    #+#             */
/*   Updated: 2025/12/18 08:13:29 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

char	*ft_find_path(char **envp)
{
	const char	*path = "PATH=";
	int			i;

	while (*envp)
	{
		i = 0;
		if (!ft_strncmp(*envp, path, 5))
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}

int	ft_parse_cmd(int ac, char **av, char **envp, char **path_list)
{
	char	**cmd;
	char	*path;
	int		i;
	int		j;

	i = 0;
	while (i < ac)
	{
		j = 0;
		while (1)
		{
			cmd = ft_split(av[i], ' ');
			path = ft_super_join(path_list[j], cmd[0], '/');
			if (access(path, X_OK) == 0)
				ft_process_cmd(path, cmd, envp, av[ac]);
			else
				free(path);
			if (!path_list[++j])
				return (1);
		}
	}
	return (0);
}

void	ft_process_cmd(char *path, char **cmd, char **envp, char *outfile)
{
	int	fd_out;

	fd_out = open(outfile, O_RDWR);
	dup2(fd_out, 1);
	execve(path, cmd, envp);
	close(fd_out);
}

pid_t	ft_create_pipes(int n_cmd)
{
	int	fd[2];
	while (n_cmd >= 0)
	{
		if (pipe(fd) < 0)
			return (perror("Error"), 1);
		n_cmd--;
	}
}

int	main(int ac, char **av, char **envp)
{
	const char	*path_line = ft_find_path(envp);
	char		**path_list;
	int			fd_in;
	int			fd[2];

	if (!path_line || ac < 5)
		return (perror("Error"), 1);
	path_list = ft_split(path_line, ':');
	if (ft_parse_cmd(ac, av, envp, path_list))
		return (perror("Error"), 1);
	fd_in = open(av[2], O_RDONLY);
	ft_create_pipes(ac - 3);
	close(fd_in);
	return (0);
}
