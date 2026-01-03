/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:39:11 by vbleskin          #+#    #+#             */
/*   Updated: 2025/12/19 12:59:10 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <limits.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*buffer;

	if (size != 0 && nmemb > __SIZE_MAX__ / size)
		return (NULL);
	buffer = malloc(size * nmemb);
	if (!buffer)
		return (NULL);
	ft_bzero(buffer, size * nmemb);
	return (buffer);
}
