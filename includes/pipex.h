/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 21:21:47 by vbleskin          #+#    #+#             */
/*   Updated: 2025/12/22 00:25:31 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <fcntl.h>
# include <unistd.h>

# define SUCCESS 0
# define ERROR 1
# define FAIL -1
# define TRUE 1

typedef struct s_data
{
	int		n_cmds;
	int		*pipes;
	pid_t	*pids;
} t_data

// UTILS
char			*ft_super_join(char const *s1, char const *s2, char sep);

#endif