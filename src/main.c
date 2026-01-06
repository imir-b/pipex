/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 21:21:00 by vbleskin          #+#    #+#             */
/*   Updated: 2026/01/06 03:19:12 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_is_heredoc(char *str)
{
	if (ft_strncmp(str, "here_doc", 8))
		return (FALSE);
	return (TRUE);
}

int	main(int ac, char **av, char **envp)
{
	t_data		*data;
	int			ret;
	const int	is_heredoc = ft_is_heredoc(av[1]);

	ret = 0;
	if (ac < 5)
		return (ft_error("Error: args and/or envp not valid"));
	data = ft_init_data(ac, av, envp, is_heredoc);
	if (!data)
		return (ft_error("Error: can't initialize data"));
	if (!ft_create_pipes(data))
		return (free_data(data), ft_error("Error: Failure creating pipes"));
	if (ft_process_cmds(ac - data->n_cmds - 1, av, data))
		return (free_data(data), ft_error("Error : Failure process cmds"));
	ft_close_all_fds(data);
	ret = ft_wait_pids(data);
	free_data(data);
	return (ret);
}
