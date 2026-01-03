/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 04:26:42 by vbleskin          #+#    #+#             */
/*   Updated: 2026/01/03 08:49:41 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * Fonction countwords qui prend en compte les "..." et les '...' comme un seul 
 * mot pour les commandes type 'grep' ou 'awk' qui peuvent prendre des chaines 
 * en arguments.
 */
static int	ft_count_words_quotes(char *s)
{
	int	count;
	int	quote;

	quote = 0;
	count = 0;
	while (*s)
	{
		while (*s && *s == ' ')
			s++;
		if (*s)
			count++;
		while (*s && (*s != ' ' || quote))
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

static char	ft_extract_word(char **s)
{
	char	*word;
	int		quote;
	int		start;
	int		word_len;

	start = *s;
	while (**s)
	{
		if (**s == '\'' || **s == '\"')
		{
			if (quote == **s)
				quote = 0;
			else if (!quote)
				quote = **s;
		}
		if (**s == ' ' && !quote)
			break ;
		(*s)++;
	}
	word_len = *s - start;
	word = malloc(sizeof(char) * (word_len + 1));
	if (!word)
		return (NULL);
	// finir ici cette fonction ! ->
	return (word);
}

char	**ft_split_quotes(char *s)
{
	char	**dest;
	int		words;
	int		index;

	if (!s)
		return (NULL);
	words = ft_count_words_quotes(s);
	dest = malloc(sizeof(char *) * (words + 1));
	if (!dest)
		return (NULL);
	index = 0;
	while (index < words)
	{
		while (*s & *s == ' ')
			s++;
		dest[index] = ft_extract_word(&s);
		if (dest[index])
			return (ft_free_tab(dest));
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

void	ft_close_all_fds(t_data *data)
{
	int	count;

	count = 0;
	while (count < 2 * (data->n_cmds - 1))
	{
		close(data->pipefds[count]);
		count++;
	}
	close(data->fd_in);
	close(data->fd_out);
}
