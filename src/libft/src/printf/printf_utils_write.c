/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils_write.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 11:29:13 by vbleskin          #+#    #+#             */
/*   Updated: 2025/12/19 17:38:09 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_pf_putchar(int i, t_struct *list)
{
	char	c;
	int		bytes;

	c = (char)i;
	bytes = write(1, &c, 1);
	if (bytes == -1)
		list->error = 1;
	return (bytes);
}

int	ft_pf_putstr(char *str, int len, t_struct *list)
{
	int	bytes;

	if (!str)
	{
		bytes = write(1, "(null)", 6);
		if (bytes == -1)
			list->error = 1;
		return (bytes);
	}
	bytes = write(1, str, len);
	if (bytes == -1)
		list->error = 1;
	return (bytes);
}

int	ft_pf_putnbr(int nbr, t_struct *list)
{
	int			bytes;
	long long	nb;

	bytes = 0;
	nb = (long long) nbr;
	if (nb < 0)
		nb *= -1;
	if (nb > 9)
		bytes += ft_pf_putnbr(nb / 10, list);
	bytes += ft_pf_putchar(nb % 10 + '0', list);
	return (bytes);
}

int	ft_pf_putnbrbase(unsigned long long nbr, const char *base, \
				t_struct *list)
{
	int	bytes;

	bytes = 0;
	if (nbr >= (unsigned long long)ft_pf_strlen(base))
		bytes += ft_pf_putnbrbase(nbr / ft_pf_strlen(base), base, list);
	bytes += ft_pf_putchar(base[nbr % ft_pf_strlen(base)], list);
	return (bytes);
}
