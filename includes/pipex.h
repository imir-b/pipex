/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 21:21:47 by vbleskin          #+#    #+#             */
/*   Updated: 2025/12/22 22:40:14 by vbleskin         ###   ########.fr       */
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
	int		fd_in;
	int		fd_out;
	int		*pipes;
	pid_t	*pids;
}	t_data;

//
// ------ PARSING ------
//
char			*ft_find_path(char **envp);
int				ft_parse_cmds(int ac, char **av, char **envp, char **path_list);

//
// ------ UTILS ------
//
char			*ft_super_join(char const *s1, char const *s2, char sep);

//
// ------ DATA UTILS ------
//
void			*free_data(t_data *data);
t_data			*ft_init_data(int ac, char **av);

//
// ------ ERROR ------
//
int				ft_error(char *s);

#endif