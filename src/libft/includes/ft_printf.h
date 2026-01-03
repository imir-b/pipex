/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 13:54:19 by vbleskin          #+#    #+#             */
/*   Updated: 2025/12/19 19:47:28 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stddef.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_struct
{
	int	is_minus;
	int	is_zero;
	int	is_dot;
	int	is_hash;
	int	is_space;
	int	is_plus;
	int	error;
	int	width;
	int	precision;
}	t_struct;

//
// ------ WRITE UTILS ------
//

/**
 * Ecris 'len' caractere(s) de 'str' sur la sortie standard,
 * - char *str : la chaine de caracteres source a ecrire,
 * - int len : le nombre de caractere(s) a ecrire,
 * - t_struct *list : structure pour la gestion d'erreur,
 * - ret : le nombre de bytes qui ont ete ecris ou -1 si erreur.
 */
int				ft_pf_putstr(char *str, int len, t_struct *list);

/**
 * Ecris 'nbr' sur la sortie standard,
 * - int nbr : le nombre a ecrire,
 * - t_struct *list : structure pour la gestion d'erreur,
 * - ret : le nombre de bytes qui ont ete ecris ou -1 si erreur.
 */
int				ft_pf_putnbr(int nbr, t_struct *list);

/**
 * Ecris 'nbr' en base 'base' sur la sortie standard,
 * - unsigned long long nbr : le nombre a ecrire,
 * - const char *base : la base dans laquelle on veut ecrire nbr,
 * - t_struct *list : structure pour la gestion d'erreur,
 * - ret : le nombre de bytes qui ont ete ecris ou -1 si erreur.
 */
int				ft_pf_putnbrbase(unsigned long long nbr, const char *base, \
					t_struct *list);

/**
 * Ecris le caractere 'i' sur la sortie standard,
 * - int i : le caractere a ecrire,
 * - t_struct *list : structure pour la gestion d'erreur,
 * ret : 1 si on a ecrit ou -1 si erreur.
 */
int				ft_pf_putchar(int i, t_struct *list);

//
// ------ LIST UTILS ------
//

/**
 * Alloue et initialise la structure de data avec les valeurs par defaut,
 * - ret : la liste intitialisee.
 */
t_struct		*ft_pf_init_list(void);

/**
 * Reinitialise list avec les valeurs par defaut,
 * - t_struct *list : la structure a reset,
 * - ret : void.
 */
void			ft_pf_reset_list(t_struct *list);

//
// ------ LIBFT UTILS ------
//

/**
 * Original ft_strchr de libft sans le segfault.
 */
const char		*ft_pf_strchr(const char *str, char c);

/**
 * Original ft_strlen de libft sans le segfault.
 */
int				ft_pf_strlen(const char *str);

//
// ------ UTILS ------
//

/**
 * Calcul la longueur de 'nb',
 * - long long nb : long long dont on cherche la longueur,
 * - ret : la longueur.
 */
int				ft_nbrlen(long long nb);

/**
 * Calcul la longueur de 'n' dans la base 'base_len',
 * - unsigned long long n : unsigned long long dont on cherche la longueur,
 * - int base_len : la base dans laquelle est n,
 * - ret : la longueur.
 */
int				ft_nbaselen(unsigned long long n, int base_len);

/**
 * Verifie si la premiere lettre trouvee dans 'str' est majuscule,
 * - const char *str : la chaine de caracteres a verifier,
 * - ret : 0 si pas de lettre ou la premiere lettre trouvee est minuscule,
 * - ret : 1 si la premiere lettre est majuscule.
 */
int				ft_is_str_upper(const char *str);

/**
 * Itere dans 's' tant qu'on lit des chiffres et converti le nombre lu en int,
 * - char **s : un pointeur vers la chaine a lire,
 * - ret : le nombre lu dans s converti en int.
 */
int				ft_atoi_move(char **s);

//
// ------ HANDLE TYPES ------
//

/**
 * Gere et ecris les arguments de type int et recupere les flags, -
 * la precision et la largeur dans 'list' pour les ajustements necessaires,
 * - int nb : le nombre a ecrire,
 * - t_struct *list : structure pour la data et la gestion d'erreur,
 * - ret : le nombre de bytes qu'on a ecrit.
 */
int				ft_handle_int(int nb, t_struct *list);

/**
 * Gere les arguments de type char et recupere les flags, -
 * la precision et la largeur dans 'list' pour les ajustements necessaires,
 * - int c : le caractere a ecrire,
 * - t_struct *list : structure pour la data et la gestion d'erreur,
 * - ret : le nombre de bytes qu'on a ecrit.
 */
int				ft_handle_char(int c, t_struct *list);

/**
 * Gere les arguments de type char * et recupere les flags, -
 * la precision et la largeur dans 'list' pour les ajustements necessaires,
 * - char *str : la chaine de caracteres a ecrire,
 * - t_struct *list : structure pour la data et la gestion d'erreur,
 * - ret : le nombre de bytes qu'on a ecrit.
 */
int				ft_handle_str(char *str, t_struct *list);

/**
 * Gere les arguments de type unsigned int dans la base 'base' et recupere les -
 * flags, la precision et la largeur dans 'list' pour les ajustements -
 * necessaires,
 * - unsigned int n : le nombre a ecrire,
 * - const char *base : la base dans laquelle on veut ecrire 'n'
 * - t_struct *list : structure pour la data et la gestion d'erreur,
 * - ret : le nombre de bytes qu'on a ecrit.
 */
int				ft_handle_nbrbase(unsigned int n, const char *base, \
					t_struct *list);

/**
 * Gere les arguments de type void * et recupere les flags, -
 * la precision et la largeur dans 'list' pour les ajustements necessaires,
 * - void *ptr : le pointeur void a ecrire,
 * - t_struct *list : structure pour la data et la gestion d'erreur,
 * - ret : le nombre de bytes qu'on a ecrit.
 */
int				ft_handle_ptr(void *ptr, t_struct *list);

//
// ------ PARSING ------
//

/**
 * Ecris le caractere 'c' un nombre 'width' - 'len' de fois,
 * - int width : la largeur totale "attendue" donnee en flag du printf,
 * - int len : la taille de l'element a afficher sans padding,
 * - char c : le caractere a repeter pour le padding,
 * - t_struct *list : structure pour la data et la gestion d'erreur,
 * - ret : le nombre de caracteres qu'on a affiche.
 */
int				ft_put_padding(int width, int len, char c, t_struct *list);

/**
 * Cherche si des flags (-0# +) sont dans 's' et met a jour les bool de 'list',
 * - char *s : la chaine de caractere dans laquelle on cherche les flags,
 * - t_struct *list : structure pour la data (booleens pour chaque flag),
 * - ret : un pointeur sur le dernier flag lu dans s
 */
char			*ft_check_flags(char *s, t_struct *list);

/**
 * Parcours 's', cherche '%' dedans et appelle les fonctions pour ecrire ou -
 * ft_process_percent pour lire et ecrire les arguments,
 * - const char *s : la chaine de caractere qu'on donne a ft_printf,
 * - va_list args : les arguments qu'on donne a ft_printf,
 * - t_struct *list : structure pour la data et la gestion d'erreur,
 * - ret : la longueur de tout ce qu'on a ecrit ou -1 en cas d'erreur.
 */
int				ft_parsing(const char *s, va_list args, t_struct *list);

//
// ------ FT_PRINTF -------
//

/**
 * Reproduit le comportement de la fonction standard printf.
 * Gere les conversions cspdiuxX%, la largeur de champ, la precision -
 * ainsi que les flags suivants :
 * - '-' (alignement gauche), '0' (padding zero), '.' (precision),
 * - '#' (prefixe 0x/0X), ' ' (espace si positif) et '+' (force le signe).
 * - const char *s : la chaine de format contenant le texte et les '%...',
 * - ... : les arguments variables correspondant aux conversions,
 * - ret : le nombre total de caracteres imprimes ou -1 en cas d'erreur.
 */
int				ft_printf(const char *s, ...);

#endif