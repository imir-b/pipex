/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 22:35:15 by vbleskin          #+#    #+#             */
/*   Updated: 2025/12/22 22:46:52 by vbleskin         ###   ########.fr       */
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

int	ft_parse_cmds(int ac, char **av, char **envp, char **path_list)
{
	char	**cmd;
	char	*path;
	int		args;
	int		cur_path;

	args = 2;
	while (args < ac)
	{
		cur_path = 0;
		while (TRUE)
		{
			cmd = ft_split(av[args], ' ');
			path = ft_super_join(path_list[cur_path], cmd[0], '/');
			if (access(path, X_OK) == 0)
				ft_process_cmd(path, cmd, av[1], av[ac]);
			else
				free(path);
			if (!path_list[++cur_path])
				break ;
		}
	}
	return (SUCCESS);
}
