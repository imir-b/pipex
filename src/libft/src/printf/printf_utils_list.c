/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 11:59:53 by vbleskin          #+#    #+#             */
/*   Updated: 2025/12/19 15:25:00 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_struct	*ft_pf_init_list(void)
{
	t_struct	*list;

	list = malloc(sizeof(t_struct));
	if (!list)
		return (NULL);
	list->error = 0;
	list->width = 0;
	list->precision = -1;
	list->is_minus = 0;
	list->is_zero = 0;
	list->is_dot = 0;
	list->is_hash = 0;
	list->is_space = 0;
	list->is_plus = 0;
	return (list);
}

void	ft_pf_reset_list(t_struct *list)
{
	list->width = 0;
	list->precision = -1;
	list->is_minus = 0;
	list->is_zero = 0;
	list->is_dot = 0;
	list->is_hash = 0;
	list->is_space = 0;
	list->is_plus = 0;
}
