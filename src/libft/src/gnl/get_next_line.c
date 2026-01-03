/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 02:05:20 by vbleskin          #+#    #+#             */
/*   Updated: 2025/12/19 19:21:11 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_add_to_stash(int fd, char *stash, int *end)
{
	char		*buffer;
	char		*readed;
	ssize_t		bytes;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(stash), *end = -1, NULL);
	bytes = read(fd, buffer, BUFFER_SIZE);
	if (bytes < 0)
		return (free(stash), free(buffer), *end = -1, NULL);
	if (bytes == 0)
		return (*end = 1, free(buffer), stash);
	buffer[bytes] = '\0';
	if (ft_gnl_strchr(buffer, '\n'))
		*end = 1;
	readed = ft_gnl_realloc(stash, buffer);
	free(buffer);
	if (!readed)
		return (*end = -1, NULL);
	if (bytes < BUFFER_SIZE)
		return (*end = 1, readed);
	return (readed);
}

char	*ft_clean_stash(char **stash)
{
	char	*new_stash;
	char	*nl;
	int		i;

	nl = ft_gnl_strchr(*stash, '\n');
	nl++;
	if (*nl == '\0')
		return (free(*stash), NULL);
	new_stash = malloc(ft_gnl_strlen(nl) + 1);
	if (!new_stash)
		return (free(*stash), NULL);
	i = 0;
	new_stash[i] = '\0';
	while (nl[i])
	{
		new_stash[i] = nl[i];
		i++;
	}
	new_stash[i] = '\0';
	return (free(*stash), new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[FD_MAX];
	char		*line;
	char		*nl;
	int			end;

	end = 0;
	if (fd < 0 || fd >= FD_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	while (!end && (!stash[fd] || !ft_gnl_strchr(stash[fd], '\n')))
		stash[fd] = ft_add_to_stash(fd, stash[fd], &end);
	if (end == -1)
		return (NULL);
	if (!stash[fd])
		return (NULL);
	nl = ft_gnl_strchr(stash[fd], '\n');
	if (nl)
	{
		line = ft_strndup(stash[fd], nl - stash[fd] + 1);
		if (!line)
			return (free(stash[fd]), stash[fd] = NULL, NULL);
		stash[fd] = ft_clean_stash(&stash[fd]);
		return (line);
	}
	line = stash[fd];
	return (stash[fd] = NULL, line);
}
