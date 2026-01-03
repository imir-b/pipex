/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 13:38:39 by vbleskin          #+#    #+#             */
/*   Updated: 2025/12/19 15:29:54 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *s, ...)
{
	va_list		args;
	t_struct	*list;
	int			len;

	if (s == NULL)
		return (-1);
	len = 0;
	list = ft_pf_init_list();
	if (!list)
		return (-1);
	va_start(args, s);
	len = ft_parsing(s, args, list);
	va_end(args);
	if (list->error == 1)
		return (free(list), -1);
	return (free(list), len);
}
