/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:38:41 by vbleskin          #+#    #+#             */
/*   Updated: 2025/11/12 17:08:25 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	littlelen;

	if (little[0] == '\0')
		return ((char *)big);
	i = 0;
	littlelen = (size_t)ft_strlen(little);
	while (big[i] && i < len)
	{
		j = 0;
		while (i + j < len && big[i + j] && big[i + j] == little[j])
			j++;
		if (j == littlelen)
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}
