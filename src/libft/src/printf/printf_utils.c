/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 11:58:29 by vbleskin          #+#    #+#             */
/*   Updated: 2025/12/19 17:01:48 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_nbrlen(long long nb)
{
	int	len;

	len = 0;
	if (nb == 0)
		return (1);
	while (nb)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

int	ft_atoi_move(char **s)
{
	int	nb;

	nb = 0;
	if (!s || !*s)
		return (-1);
	while (**s && ft_isdigit((int)**s))
	{
		nb = nb * 10 + (**s - '0');
		(*s)++;
	}
	return (nb);
}

int	ft_nbaselen(unsigned long long n, int base_len)
{
	int	len;

	len = 1;
	while (n >= (unsigned long long)base_len)
	{
		n /= base_len;
		len++;
	}
	return (len);
}

int	ft_is_str_upper(const char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (ft_islower((int)*str))
			return (0);
		else if (ft_isupper((int)*str))
			return (1);
		str++;
	}
	return (0);
}
