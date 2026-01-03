/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:47:09 by vbleskin          #+#    #+#             */
/*   Updated: 2025/12/29 23:09:48 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "printf.h"
# include "get_next_line.h"
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

//
// ------ FONCTIONS DE MANIPULATION & VERIFICATION DE CARACTERES ------
//

/**
 * Verifie si un caractere est une lettre majuscule ou minuscule,
 * - int c : le caractere a verifier,
 * - return : une valeur si VRAI et 0 si FAUX.
 */
int			ft_isalpha(int c);

/**
 * Verifie si un caractere est un chiffre,
 * - int c : le caractere a verifier,
 * - return : une valeur si VRAI et 0 si FAUX.
 */
int			ft_isdigit(int c);

/**
 * Verifie si un caractere est alpha-numerique,
 * - int c : le caractere a verifier,
 * - return : une valeur si VRAI et 0 si FAUX.
 */
int			ft_isalnum(int c);

/**
 * Verifie si un caractere est dans la table ASCII,
 * - int c : le caractere a verifier,
 * - return : une valeur si VRAI et 0 si FAUX.
 */
int			ft_isascii(int c);

/**
 * Verifie si un caractere est printable,
 * - int c : le caractere a verifier,
 * - return : une valeur si VRAI et 0 si FAUX.
 */
int			ft_isprint(int c);

/**
 * Verifie si un caractere est une lettre majuscule,
 * - int c : le caractere a verifier,
 * - return : une valeur si VRAI et 0 si FAUX.
 */
int			ft_isupper(int c);

/**
 * Verifie si un caractere est une lettre minuscule,
 * - int c : le caractere a verifier,
 * - return : une valeur si VRAI et 0 si FAUX.
 */
int			ft_islower(int c);

/**
 * Convertit une lettre minuscule en majuscule,
 * - int c : le caractere a convertir,
 * - return : le caractere converti ou c inchange.
 */
int			ft_toupper(int c);

/**
 * Convertit une lettre majuscule en minuscule,
 * - int c : le caractere a convertir,
 * - return : le caractere converti ou c inchange.
 */
int			ft_tolower(int c);

//
// ------ FONCTIONS DE MANIPULATION & RECHERCHE DE CHAINES DE CARACTERES ------
//

/**
 * Calcule la longueur d'une chaine de caracteres,
 * - const char *str : la chaine de caracteres,
 * - return : la longueur de la chaine,
 * - [!] segfault si la chaine ne fini pas par '\0'.
 */
int			ft_strlen(const char *str);

/**
 * Copie jusqu'a s caractere(s) de src dans dest et termine par '\0',
 * - char *dest : la chaine dans laquelle on essaye de copier,
 * - const char *src : la chaine qu'on essaye de copier,
 * - size_t s : le nombre de caractere(s) qu'on veut copier,
 * - return : la taille totale de la chaine qu'on essaye de creer.
 */
size_t		ft_strlcpy(char *dest, const char *src, size_t s);

/**
 * Concatene src a la fin de dest en garantissant la terminaison '\0',
 * - char *dest : la chaine de destination,
 * - const char *src : la chaine a ajouter,
 * - size_t s : la taille totale du buffer dest,
 * - return : la longueur totale de la chaine qu'on a essaye de creer.
 */
size_t		ft_strlcat(char *dest, const char *src, size_t s);

/**
 * Cherche la premiere occurrence d'un caractere dans une chaine,
 * - const char *s : la chaine a analyser,
 * - int c : le caractere a rechercher,
 * - return : un pointeur vers le caractere trouve ou NULL.
 */
char		*ft_strchr(const char *s, int c);

/**
 * Cherche la derniere occurrence d'un caractere dans une chaine,
 * - const char *s : la chaine a analyser,
 * - int c : le caractere a rechercher,
 * - return : un pointeur vers le caractere trouve ou NULL.
 */
char		*ft_strrchr(const char *s, int c);

/**
 * Compare deux chaines sur au plus n caracteres,
 * - const char *s1 : la premiere chaine,
 * - const char *s2 : la seconde chaine,
 * - size_t n : le nombre max de caracteres a comparer,
 * - return : la difference entre les deux premiers caracteres differents.
 */
int			ft_strncmp(const char *s1, const char *s2, size_t n);

/**
 * Cherche une sous-chaine dans une chaine (taille limitee),
 * - const char *big : la chaine dans laquelle chercher,
 * - const char *little : la sous-chaine a trouver,
 * - size_t len : nombre max de caracteres a fouiller dans big,
 * - return : un pointeur vers le debut de la sous-chaine ou NULL.
 */
char		*ft_strnstr(const char *big, const char *little, size_t len);

/**
 * Duplique une chaine de caracteres,
 * - const char *s : la chaine a dupliquer,
 * - return : un pointeur vers la nouvelle chaine ou NULL.
 */
char		*ft_strdup(const char *s);

/**
 * Duplique jusqu'a 'n' caracteres de la chaine 'src'
 * - const char *src : la chaine a dupliquer,
 * - size_t n : le nombre de caracteres a dupliquer,
 * - return : un pointeur vers la nouvelle chaine ou NULL.
 */
char		*ft_strndup(char *src, size_t n);

/**
 * Alloue et retourne une sous-chaine a partir de s,
 * - char const *s : la chaine d'origine,
 * - unsigned int start : l'index de depart,
 * - size_t len : la taille max de la sous-chaine,
 * - return : la sous-chaine allouee ou NULL.
 */
char		*ft_substr(char const *s, unsigned int start, size_t len);

/**
 * Alloue et retourne la concatenation de s1 et s2,
 * - char const *s1 : la premiere chaine,
 * - char const *s2 : la seconde chaine,
 * - return : la nouvelle chaine ou NULL.
 */
char		*ft_strjoin(char const *s1, char const *s2);

/**
 * Alloue et retourne une copie de s1 sans les caracteres set au debut/fin,
 * - char const *s1 : la chaine a nettoyer,
 * - char const *set : les caracteres a retirer,
 * - return : la chaine nettoyee ou NULL.
 */
char		*ft_strtrim(char const *s1, char const *set);

/**
 * Alloue et retourne un tableau de chaines obtenu en separant s par c,
 * - char const *s : la chaine a decouper,
 * - char c : le caractere separateur,
 * - return : le tableau de chaines (termine par NULL) ou NULL.
 */
char		**ft_split(char const *s, char c);

/**
 * Applique la fonction f a chaque caractere de s pour creer une nouvelle chaine,
 * - char const *s : la chaine source,
 * - char (*f) : la fonction a appliquer,
 * - return : la nouvelle chaine modifiee ou NULL.
 */
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/**
 * Applique la fonction f a chaque caractere de s (modification sur place),
 * - char *s : la chaine a modifier,
 * - void (*f) : la fonction a appliquer.
 */
void		ft_striteri(char *s, void (*f)(unsigned int, char*));

//
// ------ FONCTIONS DE CONVERSION ------
//

/**
 * Convertit le debut d'une chaine en entier (atoi),
 * - const char *str : la chaine a convertir,
 * - return : l'entier converti.
 */
int			ft_atoi(const char *str);

/**
 * Alloue et retourne une chaine representant l'entier n,
 * - int n : l'entier a convertir,
 * - return : la chaine representant l'entier ou NULL.
 */
char		*ft_itoa(int n);

//
// ------ FONCTIONS D'ALLOCATIONS & MANIPULATION DE MEMOIRE ------
//

/**
 * Cherche un caractere dans une zone memoire,
 * - const void *s : la zone memoire,
 * - int c : le caractere a chercher,
 * - size_t n : la taille de la zone a analyser,
 * - return : un pointeur vers l'octet trouve ou NULL.
 */
void		*ft_memchr(const void *s, int c, size_t n);

/**
 * Compare deux zones memoire,
 * - const void *s1 : la premiere zone,
 * - const void *s2 : la seconde zone,
 * - size_t n : le nombre d'octets a comparer,
 * - return : la difference entre les deux premiers octets differents.
 */
int			ft_memcmp(const void *s1, const void *s2, size_t n);

/**
 * Remplit une zone memoire avec un octet constant,
 * - void *s : le pointeur vers la zone memoire,
 * - int c : l'octet a ecrire (converti en unsigned char),
 * - size_t n : le nombre d'octets a remplir,
 * - return : un pointeur vers la zone memoire s.
 */
void		*ft_memset(void *s, int c, size_t n);

/**
 * Met a zero des octets dans une zone memoire,
 * - void *s : le pointeur vers la zone memoire,
 * - size_t n : le nombre d'octets a mettre a zero.
 */
void		ft_bzero(void *s, size_t n);

/**
 * Copie une zone memoire (sans gestion de chevauchement),
 * - void *dest : la zone de destination,
 * - const void *src : la zone source,
 * - size_t n : le nombre d'octets a copier,
 * - return : un pointeur vers dest.
 */
void		*ft_memcpy(void *dest, const void *src, size_t n);

/**
 * Copie une zone memoire (gere le chevauchement),
 * - void *dest : la zone de destination,
 * - const void *src : la zone source,
 * - size_t n : le nombre d'octets a copier,
 * - return : un pointeur vers dest.
 */
void		*ft_memmove(void *dest, const void *src, size_t n);

/**
 * Alloue la memoire pour un tableau et met tout a zero,
 * - size_t nmemb : nombre d'elements,
 * - size_t size : taille d'un element,
 * - return : un pointeur vers la memoire allouee ou NULL.
 */
void		*ft_calloc(size_t nmemb, size_t size);

//
// ------ FONCTIONS D'ECRITURE (file descriptor) ------
//

/**
 * Ecrit le caractere c sur le descripteur de fichier fd,
 * - char c : le caractere a ecrire,
 * - int fd : le descripteur de fichier.
 */
void		ft_putchar_fd(char c, int fd);

/**
 * Ecrit la chaine s sur le descripteur de fichier fd,
 * - char *s : la chaine a ecrire,
 * - int fd : le descripteur de fichier.
 */
void		ft_putstr_fd(char *s, int fd);

/**
 * Ecrit la chaine s suivie d'un retour a la ligne sur fd,
 * - char *s : la chaine a ecrire,
 * - int fd : le descripteur de fichier.
 */
void		ft_putendl_fd(char *s, int fd);

/**
 * Ecrit l'entier n sur le descripteur de fichier fd,
 * - int n : l'entier a ecrire,
 * - int fd : le descripteur de fichier.
 */
void		ft_putnbr_fd(int n, int fd);

// ------ FONCTIONS DE MANIPULATION DE LISTES CHAINEES (Bonus) ------

/**
 * Alloue et retourne un nouvel element de liste,
 * - void *content : le contenu de l'element,
 * - return : le nouvel element ou NULL.
 */
t_list		*ft_lstnew(void *content);

/**
 * Ajoute l'element new au debut de la liste lst,
 * - t_list **lst : l'adresse du pointeur vers le premier element,
 * - t_list *new : l'element a ajouter.
 */
void		ft_lstadd_front(t_list **lst, t_list *new);

/**
 * Compte le nombre d'elements de la liste,
 * - t_list *lst : le debut de la liste,
 * - return : la taille de la liste.
 */
int			ft_lstsize(t_list *lst);

/**
 * Renvoie le dernier element de la liste,
 * - t_list *lst : le debut de la liste,
 * - return : le dernier element.
 */
t_list		*ft_lstlast(t_list *lst);

/**
 * Ajoute l'element new a la fin de la liste,
 * - t_list **lst : l'adresse du pointeur vers le premier element,
 * - t_list *new : l'element a ajouter.
 */
void		ft_lstadd_back(t_list **lst, t_list *new);

/**
 * Supprime et libere la memoire d'un element,
 * - t_list *lst : l'element a supprimer,
 * - void (*del) : la fonction permettant de supprimer le contenu.
 */
void		ft_lstdelone(t_list *lst, void (*del)(void*));

/**
 * Supprime et libere la liste et ses suites,
 * - t_list **lst : l'adresse du pointeur vers le premier element,
 * - void (*del) : la fonction permettant de supprimer le contenu.
 */
void		ft_lstclear(t_list **lst, void (*del)(void*));

/**
 * Itere sur la liste et applique f au contenu de chaque element,
 * - t_list *lst : le debut de la liste,
 * - void (*f) : la fonction a appliquer.
 */
void		ft_lstiter(t_list *lst, void (*f)(void *));

/**
 * Itere sur la liste et applique f pour creer une nouvelle liste,
 * - t_list *lst : le debut de la liste source,
 * - void *(*f) : la fonction a appliquer,
 * - void (*del) : la fonction pour supprimer en cas d'erreur d'alloc,
 * - return : la nouvelle liste ou NULL.
 */
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif