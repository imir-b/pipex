/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 22:34:28 by vbleskin          #+#    #+#             */
/*   Updated: 2026/01/19 05:57:25 by vbleskin         ###   ########.fr       */
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
 * Decoupage de ft_init_data pour faire les open, on a un calcul different
 * pour 'n_cmds' quand on a un here_doc a cause du 'limiter' qui fait un 
 * argument en plus.
 */
static int	ft_init_files(t_data *data, int ac, char **av, int heredoc)
{
	if (heredoc)
	{
		if (ac < 6)
			return (ft_error(ARG_ERR));
		data->n_cmds = ac - 4;
		data->fd_in = ft_handle_heredoc(av[2]);
		if (data->fd_in == FAIL)
			return (ft_error(HEREDOC_ERR));
		data->fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else
	{
		data->n_cmds = ac - 3;
		data->fd_in = open(av[1], O_RDONLY);
		if (data->fd_in == FAIL)
			perror(av[1]);
		data->fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (data->fd_out == FAIL)
		return (perror(av[ac - 1]), ERROR);
	return (SUCCESS);
}

/**
 * Fonction pour initialiser la data de pipex :
 * - 'n_cmds' -> le nombre de commandes,
 * - 'path_list' -> les differents path qu'on a trouve dans envp,
 * - 'pipefds' -> un tableau avec les fds de chaque pipe,
 * - 'pids' -> les adresses 'pids' de chaque fork,
 * - 'fd_in' -> le fd correspondant au fichier 'infile',
 * - 'fd_out' -> le fd correspondant au fichier 'outfile',
 * - 'envp' -> envp qui est stocke dans cette structure.
 */
t_data	*ft_init_data(int ac, char **av, char **envp, int heredoc)
{
	t_data		*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (NULL);
	data->envp = envp;
	data->path_list = ft_split(ft_find_path(envp), ':');
	if (!data->path_list)
		return (free_data(data));
	if (ft_init_files(data, ac, av, heredoc))
		return (free_data(data));
	data->pipefds = malloc(sizeof(int) * 2 * (data->n_cmds - 1));
	if (!data->pipefds)
		return (free_data(data));
	data->pids = malloc(sizeof(pid_t) * data->n_cmds);
	if (!data->pids)
		return (free_data(data));
	return (data);
}

/**
 * Fonction qui cherche le chemin dans 'paths' associe a la commande
 * On test 1 par 1 les chemins qu'on concatene avec la commande puis
 * avec 'access' on test si le chemin est le bon.
 */
static char	*ft_scan_bin_paths(char **paths, char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths && paths[i])
	{
		full_path = ft_super_join(paths[i], cmd, '/');
		if (full_path && access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

/**
 * Prepare une commande pour la donner a execve qui demande la 
 * commande 'splite' et le path de la commande pour fonctionner.
 * On test si la commande ne contient pas deja son path, sinon
 * on appelle ft_scan_bin_paths pour trouver le bon path.
 * On stock ces 2 informations dans une structure 'cmd_data'.
 */
t_cmd_data	*ft_init_cmd_data(char *cmd_line, char **path_list)
{
	t_cmd_data	*data;

	data = ft_calloc(1, sizeof(t_cmd_data));
	if (!data)
		return (NULL);
	data->cmd = ft_split_quotes(cmd_line, ' ');
	if (!data->cmd || !data->cmd[0])
		return (free_cmd_data(data));
	if (ft_strrchr(data->cmd[0], '/') && access(data->cmd[0], X_OK) == 0)
		data->path = ft_strdup(data->cmd[0]);
	else
		data->path = ft_scan_bin_paths(path_list, data->cmd[0]);
	if (!data->path)
		return (free_cmd_data(data));
	return (data);
}
