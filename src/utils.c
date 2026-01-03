/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 04:26:42 by vbleskin          #+#    #+#             */
/*   Updated: 2026/01/03 22:58:32 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * Fonction countwords qui prend en compte les "..." et les '...' comme un seul 
 * mot pour les commandes type 'grep' ou 'awk' qui peuvent prendre des chaines 
 * en arguments.
 */
static int	ft_count_words_quotes(char *s, char sep)
{
	int	count;
	int	quote;

	quote = 0;
	count = 0;
	while (*s)
	{
		while (*s && *s == sep)
			s++;
		if (*s)
			count++;
		while (*s && (*s != sep || quote))
		{
			if (*s == '\'' || *s == '\"')
			{
				if (quote == *s)
					quote = 0;
				else if (!quote)
					quote = *s;
			}
			s++;
		}
	}
	return (count);
}

static int	ft_word_len_quotes(char *s, char sep)
{
	char	*start;
	int		len;
	int		quote;

	start = s;
	quote = 0;
	while (*s)
	{
		if (*s == '\'' || *s == '\"')
		{
			if (quote == *s)
				quote = 0;
			else if (!quote)
				quote = *s;
		}
		if (*s == sep && !quote)
			break ;
		s++;
	}
	len = s - start;
	return (len);
}

static char	*ft_extract_word_quotes(char **s, char sep)
{
	char	*word;
	int		len;
	int		quote;
	int		i;

	len = ft_word_len_quotes(*s, sep);
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	quote = 0;
	while (len-- > 0)
	{
		if ((**s == '\'' || **s == '\"') && (!quote || quote == **s))
			quote ^= **s;
		else
			word[i++] = **s;
		(*s)++;
	}
	word[i] = '\0';
	return (word);
}

/**
 * Split qui ignore les separateurs entre des quotes (' ou ") concu pour pipex
 * afin de pouvoir lire les arguments de grep ou awk entre quotes comme un 
 * seul mot.
 */
char	**ft_split_quotes(char *s, char sep)
{
	char	**dest;
	int		words;
	int		index;

	if (!s)
		return (NULL);
	words = ft_count_words_quotes(s, sep);
	dest = malloc(sizeof(char *) * (words + 1));
	if (!dest)
		return (NULL);
	index = 0;
	while (index < words)
	{
		while (*s && *s == ' ')
			s++;
		dest[index] = ft_extract_word_quotes(&s, sep);
		if (!dest[index])
			return (free_tab(dest));
		index++;
	}
	dest[index] = NULL;
	return (dest);
}

/**
 * Cette fonction agit comme un strjoin avec un separateur. Elle concatene
 * 's1' avec 's2' mais met 'sep' entre les deux chaines. Termine la chaine
 * de retour par '\0'.
 */
char	*ft_super_join(char const *s1, char const *s2, char sep)
{
	char	*str;
	int		size;
	int		i;
	int		j;

	str = NULL;
	size = sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2);
	str = malloc(size);
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i++] = sep;
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = ('\0');
	return (str);
}
