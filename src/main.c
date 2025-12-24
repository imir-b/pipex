/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 21:21:00 by vbleskin          #+#    #+#             */
/*   Updated: 2025/12/24 05:49:55 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	const char	*path_line = ft_find_path(envp);
	t_data		*data;
	int			status;

	if (!path_line || ac < 5)
		return (ft_error("Error: args and/or envp not valid"));
	data = ft_init_data(ac, av, path_line);
	if (!data)
		return (ft_error("Error: can't initialize data"));
	data->envp = envp;
	if (!ft_create_pipes(data))
		return (free_data(data), ft_error("Error: Failure creating pipes"));
	if (ft_process_cmds(av, data))
		return (free_data(data), ft_error("Error : Failure process cmds"));
	ft_close_all_fds(data);
	ft_wait_pids(data, &status);
	if (WIFEXITED(status))
		return (free_data(data), WEXITSTATUS(status));
	return (free_data(data), SUCCESS);
}
