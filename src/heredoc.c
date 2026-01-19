/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 05:54:58 by vbleskin          #+#    #+#             */
/*   Updated: 2026/01/19 05:55:08 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * Fonction qui permet de lire dans STDIN_FILENO (0) jusqu'a recuperer
 * le 'limiter' pour gerer les here_docs. On return le fd dans lequel
 * on a ecrit toutes les lignes.
 */
int	ft_handle_heredoc(char *limiter)
{
	int		fd;
	int		len;
	char	*line;

	fd = open(".tmp_heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == FAIL)
		return (FAIL);
	len = ft_strlen(limiter);
	while (TRUE)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line || (!ft_strncmp(line, limiter, len) && line[len] == '\n'))
			break ;
		write(fd, line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(fd);
	fd = open(".tmp_heredoc", O_RDONLY);
	unlink(".tmp_heredoc");
	return (fd);
}
