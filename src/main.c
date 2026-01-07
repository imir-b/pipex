/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 21:21:00 by vbleskin          #+#    #+#             */
/*   Updated: 2026/01/07 11:28:07 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_data	*data;
	int		ret;
	int		heredoc;

	ret = 0;
	if (ac < 5)
		return (ft_error(ARG_ERR));
	if (ft_strncmp(av[1], "here_doc", 8))
		heredoc = FALSE;
	else
		heredoc = TRUE;
	data = ft_init_data(ac, av, envp, heredoc);
	if (!data)
		return (ft_error(DATA_ERR));
	if (!ft_create_pipes(data))
		return (free_data(data), ft_error(PIPES_ERR));
	if (ft_process_cmds(ac - data->n_cmds - 1, av, data))
		return (free_data(data), ft_error(RUN_ERR));
	ft_close_all_fds(data);
	ret = ft_wait_pids(data);
	free_data(data);
	return (ret);
}
