/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 13:00:28 by vbleskin          #+#    #+#             */
/*   Updated: 2026/01/02 11:30:10 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_wait_pids(t_data *data)
{
	int	i;
	int	status;
	int	exit_code;

	i = 0;
	status = 0;
	exit_code = 0;
	while (i < data->n_cmds)
	{
		waitpid(data->pids[i], &status, 0);
		if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status) && WTERMSIG(status) != SIGPIPE)
			exit_code = 128 + WTERMSIG(status);
		i++;
	}
	return (exit_code);
}

void	ft_secure_dup2(int fd, int target, t_cmd_data *cmd_data, t_data *data)
{
	if (dup2(fd, target) == FAIL)
	{
		perror(DUP_ERR);
		free_cmd_data(cmd_data);
		free_data(data);
		exit(ERROR);
	}
}

void	ft_run_cmd(t_cmd_data *c_data, t_data *data, int n_cmd)
{
	if (n_cmd == 0)
	{
		ft_secure_dup2(data->fd_in, STDIN_FILENO, c_data, data);
		ft_secure_dup2(data->pipefds[1], STDOUT_FILENO, c_data, data);
	}
	else if (n_cmd == data->n_cmds - 1)
	{
		ft_secure_dup2(data->pipefds[2 * (n_cmd - 1)], STDIN_FILENO, \
						c_data, data);
		ft_secure_dup2(data->fd_out, STDOUT_FILENO, c_data, data);
	}
	else
	{
		ft_secure_dup2(data->pipefds[2 * (n_cmd - 1)], STDIN_FILENO, \
						c_data, data);
		ft_secure_dup2(data->pipefds[2 * n_cmd + 1], STDOUT_FILENO, \
						c_data, data);
	}
	ft_close_all_fds(data);
	execve(c_data->path, c_data->cmd, data->envp);
	perror(EXE_ERR);
	free_cmd_data(c_data);
	free_data(data);
	exit(ERROR);
}

int	ft_process_cmds(char **av, t_data *data)
{
	int			cmd_count;
	t_cmd_data	*cmd_data;

	cmd_count = 0;
	while (cmd_count < data->n_cmds)
	{
		data->pids[cmd_count] = fork();
		if (data->pids[cmd_count] == FAIL)
			exit(ERROR);
		if (data->pids[cmd_count] == 0)
		{
			cmd_data = ft_init_cmd_data(av[cmd_count + 2], data->path_list);
			if (!cmd_data)
			{
				ft_error(av[cmd_count + 2]);
				ft_error(": commande introuvable");
				free_data(data);
				exit(COMMAND_ERR);
			}
			ft_run_cmd(cmd_data, data, cmd_count);
			free_cmd_data(cmd_data);
		}
		cmd_count++;
	}
	return (SUCCESS);
}

int	ft_create_pipes(t_data *data)
{
	int	n_pipes;

	n_pipes = 0;
	while (n_pipes < data->n_cmds - 1)
	{
		if (pipe(data->pipefds + (2 * n_pipes)) == FAIL)
		{
			perror(PIP_ERR);
			free_data(data);
			exit(ERROR);
		}
		n_pipes++;
	}
	return (n_pipes);
}
