/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 11:23:17 by vbleskin          #+#    #+#             */
/*   Updated: 2025/12/19 12:57:39 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	long	nb;
	char	*ret;
	int		len;

	nb = (long)n;
	len = (nb <= 0);
	while (n && ++len)
		n /= 10;
	ret = ft_calloc(len - 1, sizeof(char));
	if (!ret)
		return (NULL);
	if (nb < 0)
	{
		ret[0] = '-';
		nb = -nb;
	}
	if (nb == 0)
		ret[0] = 0;
	while (nb)
	{
		ret[--len] = (nb % 10) + '0';
		nb /= 10;
	}
	return (ret);
}
