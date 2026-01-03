/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:32:18 by vbleskin          #+#    #+#             */
/*   Updated: 2025/11/12 18:30:36 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t s)
{
	size_t	i;

	i = 0;
	if (s > 0)
	{
		while (src[i] && i < (s - 1))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = ('\0');
	}
	return (ft_strlen(src));
}
