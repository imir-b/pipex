/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 21:21:00 by vbleskin          #+#    #+#             */
/*   Updated: 2025/12/23 13:13:18 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

int	main(int ac, char **av, char **envp)
{
	const char	*path_line = ft_find_path(envp);
	t_data		*data;

	if (!path_line || ac < 5)
		return (ft_error("Error: args or envp not valid"));
	data = ft_init_data(ac, av, path_line);
	data->envp = envp;
	if (!ft_create_pipes(data))
		return (free_data(data), ft_error("Error: Failure creating pipes"));
	if (ft_process_cmds(av, data))
		return (free_data(data), ERROR);
	return (SUCCESS);
}
