/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_numbers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 01:41:21 by vlad              #+#    #+#             */
/*   Updated: 2025/12/19 18:59:14 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * Termine la fonction ft_handle_int et retourne le nombre de bytes ecrit.
 */
static int	ft_print_int(long long n, int zeros, char sign, t_struct *list)
{
	int	len;
	int	ret_len;

	ret_len = 0;
	if (n == 0 && list->precision == 0)
		len = 0;
	else
		len = ft_nbrlen(n) + zeros + (sign != 0);
	if (!list->is_zero && !list->is_minus)
		ret_len += ft_put_padding(list->width, len, ' ', list);
	if (sign)
		ret_len += ft_pf_putchar(sign, list);
	if (list->is_zero && !list->is_minus)
		ret_len += ft_put_padding(list->width, len, '0', list);
	while (zeros-- > 0)
		ret_len += ft_pf_putchar('0', list);
	if (n != 0 || list->precision != 0)
		ret_len += ft_pf_putnbr(n, list);
	if (list->is_minus)
		ret_len += ft_put_padding(list->width, len, ' ', list);
	return (ret_len);
}

int	ft_handle_int(int nb, t_struct *list)
{
	long long	n;
	int			len;
	int			zeros;
	char		sign;

	n = (long long)nb;
	sign = ((zeros = 0));
	if (n < 0)
	{
		n = -n;
		sign = '-';
	}
	else if (list->is_plus)
		sign = '+';
	else if (list->is_space)
		sign = ' ';
	if (list->precision >= 0)
		list->is_zero = 0;
	len = ft_nbrlen(n);
	if (list->precision > len)
		zeros = list->precision - len;
	return (ft_print_int(n, zeros, sign, list));
}

int	ft_print_hex(unsigned long long n, int zeros, const char *base, \
	t_struct *list)
{
	int	ret_len;
	int	len;
	int	prefix_len;

	prefix_len = ((ret_len = 0));
	if (list->is_hash && n != 0)
		prefix_len = 2;
	len = ft_nbaselen(n, ft_pf_strlen(base)) + zeros + prefix_len;
	if (n == 0 && list->precision == 0)
		len = 0;
	if (!list->is_minus && !list->is_zero)
		ret_len += ft_put_padding(list->width, len, ' ', list);
	if (prefix_len && ft_is_str_upper(base))
		ret_len += ft_pf_putstr("0X", 2, list);
	else if (prefix_len)
		ret_len += ft_pf_putstr("0x", 2, list);
	if (!list->is_minus && list->is_zero)
		ret_len += ft_put_padding(list->width, len, '0', list);
	while (zeros-- > 0)
		ret_len += ft_pf_putchar('0', list);
	if (n != 0 || list->precision != 0)
		ret_len += ft_pf_putnbrbase(n, base, list);
	if (list->is_minus)
		ret_len += ft_put_padding(list->width, len, ' ', list);
	return (ret_len);
}

int	ft_handle_nbrbase(unsigned int nb, const char *base, t_struct *list)
{
	int					len;
	int					zeros;
	unsigned long long	n;

	n = (unsigned long long)nb;
	if (list->precision >= 0)
		list->is_zero = 0;
	len = ft_nbaselen(n, ft_pf_strlen(base));
	if (n == 0 && list->precision == 0)
		len = 0;
	zeros = 0;
	if (list->precision > len)
		zeros = list->precision - len;
	return (ft_print_hex(n, zeros, base, list));
}
