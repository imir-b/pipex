/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 22:34:28 by vbleskin          #+#    #+#             */
/*   Updated: 2026/01/06 03:19:52 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * Fonction pour recuperer la ligne commencant par 'PATH=' dans l'environnement
 * envp.
 */
char	*ft_find_path(char **envp)
{
	const char	*path = "PATH=";

	if (!envp)
		return (NULL);
	while (*envp)
	{
		if (!ft_strncmp(*envp, path, 5))
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}

/**
 * Fonction pour free propremment la structure 'data'.
 */
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

int	ft_handle_heredoc(char *limiter)
{
	int		pipefd[2];
	int		len;
	char	*line;

	if (pipe(pipefd) == FAIL)
		return (FAIL);
	len = ft_strlen(limiter);
	while (TRUE)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (!ft_strncmp(line, limiter, len) && line[len] == '\n')
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		free(line);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}

/**
 * Fonction pour initialiser la data de pipex :
 * - n_cmds -> le nombre de commandes.
 * - path_list -> les differents path qu'on a trouve dans envp
 * - pipefds -> un tableau avec les fds de chaque pipe
 * - pids -> les adresses 'pids' de chaque fork
 * - fd_in -> le fd correspondant au fichier 'infile'
 * - fd_out -> le fd correspondant au fichier 'outfile'
 * On a aussi 'envp' qui est stocke dans cette structure depuis le main.
 */
t_data	*ft_init_data(int ac, char **av, char **envp, int is_heredoc)
{
	t_data		*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (NULL);
	data->envp = envp;
	data->path_list = ft_split(ft_find_path(envp), ':');
	if (!data->path_list)
		return (free_data(data));
	if (is_heredoc)
	{
		if (ac < 6)
			return (free_data(data));
		data->n_cmds = ac - 4;
		data->fd_in = ft_handle_heredoc(av[2]);
	}
	else
	{
		data->n_cmds = ac - 3;
		data->fd_in = open(av[1], O_RDONLY);
		if (data->fd_in == FAIL)
			perror(av[1]);
	}
	data->fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->fd_out == FAIL)
		return (perror(av[ac - 1]), free_data(data));
	data->pipefds = malloc(sizeof(int) * 2 * (data->n_cmds - 1));
	if (!data->pipefds)
		return (free_data(data));
	data->pids = malloc(sizeof(pid_t) * data->n_cmds);
	if (!data->pids)
		return (free_data(data));
	return (data);
}

/**
 * Fonction pour free proprement la structure 'cmd_data'.
 */
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

/**
 * Prepare une commande pour la donner a execve qui demande la 
 * commande 'splite' et le path de la commande pour fonctionner.
 * On stock ces 2 informations dans une structure 'cmd_data'.
 */
t_cmd_data	*ft_init_cmd_data(char *cmd_line, char **path_list)
{
	t_cmd_data	*cmd_data;
	int			cur;

	cmd_data = ft_calloc(1, sizeof(t_cmd_data));
	if (!cmd_data)
		return (NULL);
	cmd_data->cmd = ft_split_quotes(cmd_line, ' ');
	if (!cmd_data->cmd || !cmd_data->cmd[0])
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
		{
			free(cmd_data->path);
			cmd_data->path = NULL;
		}
		cur++;
	}
	return (free_cmd_data(cmd_data));
}
