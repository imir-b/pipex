/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 11:41:15 by vbleskin          #+#    #+#             */
/*   Updated: 2025/12/19 15:26:59 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_check_flags(char *s, t_struct *list)
{
	const char	*flags = "-0# +";

	while (ft_pf_strchr(flags, *s) && *s)
	{
		if (*s == '-')
			list->is_minus = 1;
		else if (*s == '0')
			list->is_zero = 1;
		else if (*s == '#')
			list->is_hash = 1;
		else if (*s == ' ')
			list->is_space = 1;
		else if (*s == '+')
			list->is_plus = 1;
		s++;
	}
	return (s);
}

int	ft_put_padding(int width, int len, char c, t_struct *list)
{
	int	padding;
	int	count;
	int	bytes;

	if (len >= width)
		return (0);
	padding = width - len;
	count = ((bytes = 0));
	while (count < padding)
	{
		bytes = ft_pf_putchar((int)c, list);
		if (bytes == -1)
			return (-1);
		count++;
	}
	return (count);
}
