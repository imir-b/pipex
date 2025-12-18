/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 04:26:42 by vbleskin          #+#    #+#             */
/*   Updated: 2025/12/18 04:33:00 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_super_join(char const *s1, char const *s2, char sep)
{
	char	*str;
	int		size;
	int		i;
	int		j;

	str = NULL;
	size = sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2);
	str = malloc(size);
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i++] = sep;
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = ('\0');
	return (str);
}
