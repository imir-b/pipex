/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 11:38:24 by vbleskin          #+#    #+#             */
/*   Updated: 2025/12/19 18:44:01 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * Verifie si le caractere 'format' est 'u', 'x' ou 'X' et appelle la fonction -
 * ft_handle_nbrbase avec la base associee au bon format et 'arg',
 * - unsigned int arg : l'argument de ft_printf lie au format actuel,
 * - char format : le caractere a verifier,
 * - t_struct *list : structure pour la data et la gestion d'erreur,
 * - ret : le nombre de bytes qu'on a ecrit.
 */
static int	ft_check_base(unsigned int arg, char format, t_struct *list)
{
	int		len;
	char	*base;

	len = 0;
	base = NULL;
	if (format == 'u')
		base = "0123456789";
	if (format == 'x')
		base = "0123456789abcdef";
	if (format == 'X')
		base = "0123456789ABCDEF";
	len += ft_handle_nbrbase(arg, (const char *)base, list);
	return (len);
}

/**
 * Verifie si le caractere 'format' est compris dans "cspdiuxX%" et -
 * appelle la fonction handle associee au bon format,
 * - char format : le caractere a verifier,
 * - va_list args : les arguments de ft_printf,
 * - t_struct *list : structure pour la data et la gestion d'erreur,
 * - ret : le nombre de bytes qu'on a ecrit avec les arguments.
 */
static int	ft_check_format(char format, va_list args, t_struct *list)
{
	int			len;

	len = 0;
	if (format == 'c')
		len += ft_handle_char(va_arg(args, int), list);
	else if (format == 's')
		len += ft_handle_str(va_arg(args, char *), list);
	else if (format == 'p')
		len += ft_handle_ptr(va_arg(args, void *), list);
	else if (format == 'd' || format == 'i')
		len += ft_handle_int(va_arg(args, int), list);
	else if (format == 'u' || format == 'x' || format == 'X')
		len += ft_check_base(va_arg(args, unsigned int), format, list);
	else if (format == '%')
		len += ft_pf_putchar('%', list);
	return (len);
}

/**
 * Ecris tous les caracters de 's' avant 'next_percent',
 * - const char *s : un pointeur vers le premier caractere a ecrire,
 * - char *next_percent : un pointeur vers le prochain '%' dans 's',
 * - t_struct *list : structure pour la gestion d'erreur,
 * - ret : le nombre de bytes qu'on a ecrit.
 */
static int	ft_put_until_percent(const char *s, char *next_percent, \
				t_struct *list)
{
	int	size;
	int	bytes;

	size = next_percent - s;
	bytes = write (1, s, size);
	if (bytes == -1)
		list->error = 1;
	return (bytes);
}

/**
 * Lis les caracteres apres '%' dans 's' on apelle ft_check_flags -
 * On lis la largeur et la precision et on appelle ft_check_format -
 * Si on a pas de format, on ecrit le '%' et le reste normalement,
 * - char **s : pointeur vers un char '%' trouve dans la chaine de ft_printf,
 * - va_list args : arguments de ft_printf,
 * - t_struct *list : structure pour la data et la gestion d'erreur,
 * - ret : le nombre de bytes qu'on a ecrit.
 */
static int	ft_process_percent(char **s, va_list args, t_struct *list)
{
	int		len;
	char	*start;

	start = *s;
	(*s)++;
	*s = ft_check_flags(*s, list);
	if (ft_isdigit(**s))
		list->width = ft_atoi_move(s);
	if (**s == '.')
	{
		list->is_dot = 1;
		(*s)++;
		if (ft_isdigit(**s))
		list->precision = ft_atoi_move(s);
		else
		list->precision = 0;
	}
	if (ft_pf_strchr("cspdiuxX%", **s))
		len = ft_check_format(**s, args, list);
	else
		len = ft_pf_putstr(start, *s - start + 1, list);
	if (**s)
		(*s)++;
	return (ft_pf_reset_list(list), len);
}

int	ft_parsing(const char *s, va_list args, t_struct *list)
{
	int		len;
	char	*next_percent;

	len = 0;
	while (*s)
	{
		next_percent = (char *)ft_strchr(s, '%');
		if (next_percent)
		{
			len += ft_put_until_percent(s, next_percent, list);
			s = next_percent;
			len += ft_process_percent((char **)&s, args, list);
		}
		else
		{
			len += ft_pf_putstr((char *)s, ft_pf_strlen(s), list);
			break ;
		}
		if (list->error == 1)
			return (-1);
	}
	return (len);
}
