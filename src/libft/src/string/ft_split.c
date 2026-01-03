/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 20:24:35 by vbleskin          #+#    #+#             */
/*   Updated: 2025/12/19 13:41:50 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_free_all(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
	return (NULL);
}

static size_t	ft_wordlen(const char *start, char sep)
{
	size_t	len;

	len = 0;
	while (*(start + len) && *(start + len) != sep)
		len++;
	return (len);
}

static int	ft_countwords(const char *str, char sep)
{
	int		count;
	size_t	len;

	count = 0;
	while (*str)
	{
		if (*str != sep)
		{
			len = ft_wordlen(str, sep);
			str += len;
			count++;
		}
		else
			str++;
	}
	return (count);
}

char	**ft_split(const char *str, char sep)
{
	char		**dest;
	int			word;
	size_t		len;

	dest = malloc(sizeof(char *) * (ft_countwords(str, sep) + 1));
	if (!str || !dest)
		return (NULL);
	word = 0;
	while (*str)
	{
		if (*str != sep)
		{
			len = ft_wordlen(str, sep);
			dest[word] = malloc(sizeof(char) * (len + 1));
			if (!dest[word])
				return (ft_free_all(dest));
			ft_strlcpy(dest[word++], str, len + 1);
			str += len;
		}
		else
			str++;
	}
	dest[word] = NULL;
	return (dest);
}
