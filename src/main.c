/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 21:21:00 by vbleskin          #+#    #+#             */
/*   Updated: 2025/12/22 00:25:17 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

int	ft_error(char *s)
{
	ft_putstr_fd(s, STDERR_FILENO);
	return (ERROR);
}

void	ft_init_data(t_data *data, int ac)
{
	data->n_cmds = ac - 3;
}

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

void	ft_process_cmd(char *path, char **cmd, char **envp, char *outfile)
{
	int	fd_out;

	fd_out = open(outfile, O_RDWR);
	if (fd_out == FAIL)
		return (perror("Error"), exit(ERROR));
	if (dup2(fd_out, STDOUT_FILENO) == FAIL)
		return (perror("Error"), close(fd_out), exit(ERROR));
	close(fd_out);
}

int	ft_parse_cmds(int ac, char **av, char **envp, char **path_list)
{
	char	**cmd;
	char	*path;
	int		i;
	int		j;

	i = 0;
	while (i < ac)
	{
		j = 0;
		while (TRUE)
		{
			cmd = ft_split(av[i], ' ');
			path = ft_super_join(path_list[j], cmd[0], '/');
			if (access(path, X_OK) == 0)
				ft_process_cmd(path, cmd, envp, av[ac]);
			else
				free(path);
			if (!path_list[++j])
				break ;
		}
	}
	return (SUCCESS);
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

int	*ft_create_pipes(int n_cmds)
{
	int	*pipes;
	int	i;

	pipes = malloc(sizeof(int) * 2 * (n_cmds - 1));
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < n_cmds - 1)
	{
		if (pipe(pipes + (2 * i)) == FAIL)
			return (free(pipes), perror("Error"), NULL);
		i++;
	}
	return (pipes);
}

pid_t	*ft_create_childs()
{
	pid_t	*pids;
	int		i;

	i = 0;
	pids[i] = fork();
	if (pids[i] == FAIL)
		return (perror("Error"), NULL);
	return (pids);
}

int	main(int ac, char **av, char **envp)
{
	const char	*path_line = ft_find_path(envp);
	char		**path_list;
	int			fd_in;

	if (!path_line || ac < 5)
		return (ft_error("Error: args or envp not valid"));
	if (!ft_create_pipes(ac - 3))
		return (ft_error("Error: Failure creating pipes"));
	fd_in = open(av[1], O_RDONLY);
	if (fd_in == FAIL)
		return (perror("Error"), ERROR);
	path_list = ft_split(path_line, ':');
	if (ft_parse_cmds(ac, av, envp, path_list))
		return (ft_error("Error: Parsing failed"));
	close(fd_in);
	return (SUCCESS);
}
