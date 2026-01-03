/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_text.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 09:37:57 by vlad              #+#    #+#             */
/*   Updated: 2025/12/19 15:27:46 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_handle_str(char *str, t_struct *list)
{
	int		len;
	int		ret_len;

	if (!str)
		str = "(null)";
	len = ft_pf_strlen(str);
	if (list->precision < len && list->precision >= 0)
		len = list->precision;
	ret_len = 0;
	if (!list->is_minus)
	{
		ret_len += ft_put_padding(list->width, len, ' ', list);
	}
	ret_len += ft_pf_putstr(str, len, list);
	if (list->is_minus)
	{
		ret_len += ft_put_padding(list->width, len, ' ', list);
	}
	return (ret_len);
}

int	ft_handle_char(int c, t_struct *list)
{
	int		len;
	int		ret_len;
	char	padding;

	len = 1;
	padding = ' ';
	ret_len = 0;
	if (!list->is_minus)
	{
		ret_len += ft_put_padding(list->width, len, padding, list);
	}
	ret_len += ft_pf_putchar((char)c, list);
	if (list->is_minus)
	{
		ret_len += ft_put_padding(list->width, len, padding, list);
	}
	return (ret_len);
}

int	ft_handle_ptr(void *ptr, t_struct *list)
{
	const char	*base = "0123456789abcdef";
	int			len;
	int			ret_len;

	len = ft_nbaselen((unsigned long long)ptr, 16) + 2;
	ret_len = 0;
	if (!ptr)
	{
		len = 5;
		if (!list->is_minus)
			ret_len += ft_put_padding(list->width, len, ' ', list);
		ret_len = ft_pf_putstr("(nil)", len, list);
		if (list->is_minus)
			ret_len += ft_put_padding(list->width, len, ' ', list);
		return (ret_len);
	}
	if (!list->is_minus)
		ret_len += ft_put_padding(list->width, len, ' ', list);
	ret_len += ft_pf_putstr("0x", 2, list);
	ret_len += ft_pf_putnbrbase((unsigned long long)ptr, base, list);
	if (list->is_minus)
		ret_len += ft_put_padding(list->width, len, ' ', list);
	return (ret_len);
}
