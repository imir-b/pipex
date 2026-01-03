/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils_libft.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 15:18:53 by vbleskin          #+#    #+#             */
/*   Updated: 2025/12/19 19:04:14 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_pf_strlen(const char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len])
		len++;
	return (len);
}

const char	*ft_pf_strchr(const char *str, char c)
{
	if (!str)
		return (NULL);
	while (*str && *str != c)
		str++;
	if (*str == '\0')
		return (NULL);
	return (str);
}
