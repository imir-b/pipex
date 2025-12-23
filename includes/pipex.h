/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 21:21:47 by vbleskin          #+#    #+#             */
/*   Updated: 2025/12/23 13:45:59 by vbleskin         ###   ########.fr       */
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
	char	**path_list;
	char	**envp;
	int		n_cmds;
	int		fd_in;
	int		fd_out;
	int		*pipefds;
	pid_t	*pids;
}	t_data;

typedef struct s_cmd_data
{
	char	**cmd;
	char	*path;
}	t_cmd_data;

//
// ------ PARSING ------
//
char			*ft_find_path(char **envp);
void			*free_cmd_data(t_cmd_data *cmd_data);
t_cmd_data		*ft_init_cmd_data(char *cmd_line, char **path_list);
void			*free_data(t_data *data);
t_data			*ft_init_data(int ac, char **av, const char *path_line);

//
// ------ PROCESS ------
//
void			ft_run_cmd(t_cmd_data *cmd_data, t_data *data, int cmd_count);
int				ft_process_cmds(char **av, t_data *data);
int				ft_create_pipes(t_data *data);

//
// ------ UTILS ------
//
char			*ft_super_join(char const *s1, char const *s2, char sep);

//
// ------ ERROR ------
//
int				ft_error(char *s);
void			*free_tab(char **strs);

#endif