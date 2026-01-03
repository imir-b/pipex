/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:43:12 by vbleskin          #+#    #+#             */
/*   Updated: 2025/12/19 13:41:27 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_alloc(char **str, int size, int count)
{		
	*str = malloc(count * size);
	if (!*str)
		return (0);
	return (1);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= (unsigned int)ft_strlen(s))
	{
		if (!ft_alloc(&str, sizeof(char), 1))
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	if (len > (unsigned int)ft_strlen(s) - start)
		len = (unsigned int)ft_strlen(s) - start;
	if (!ft_alloc(&str, sizeof(char), len + 1))
		return (NULL);
	i = 0;
	while (i < len && s[i + start])
	{
		str[i] = s[i + start];
		i++;
	}
	str[i] = '\0';
	return (str);
}
