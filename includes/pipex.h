/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 21:21:47 by vbleskin          #+#    #+#             */
/*   Updated: 2026/01/07 11:34:22 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>

# define SUCCESS 0
# define ERROR 1
# define FAIL -1

# define TRUE 1
# define FALSE 0

# define ACCESS_ERR_CODE 126
# define CMD_ERR_CODE 127

# define DUP_ERR "Dup2 failed"
# define EXE_ERR "Execve failed"
# define PIP_ERR "Pipe failed"
# define CMD_ERR ": command not found"
# define ARG_ERR "Args are not valid"
# define HEREDOC_ERR "Failed handle heredoc"
# define DATA_ERR "Can't initialize data"
# define PIPES_ERR "Failure creating pipes"
# define RUN_ERR "Failure process cmds"

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

// -----------------------------------------------------------------------------
// PARSING
// -----------------------------------------------------------------------------
char			*ft_find_path(char **envp);
t_cmd_data		*ft_init_cmd_data(char *cmd_line, char **path_list);
t_data			*ft_init_data(int ac, char **av, char **envp, int heredoc);
int				ft_handle_heredoc(char *limiter);

// -----------------------------------------------------------------------------
// PROCESS
// -----------------------------------------------------------------------------
void			ft_run_cmd(t_cmd_data *cmd_data, t_data *data, int cmd_count);
int				ft_process_cmds(int args, char **av, t_data *data);
int				ft_create_pipes(t_data *data);
int				ft_wait_pids(t_data *data);

// -----------------------------------------------------------------------------
// UTILS
// -----------------------------------------------------------------------------
char			*ft_super_join(char const *s1, char const *s2, char sep);
char			**ft_split_quotes(char *s, char sep);

// -----------------------------------------------------------------------------
// UTILS FREE
// -----------------------------------------------------------------------------

void			ft_close_all_fds(t_data *data);
void			*free_tab(char **strs);
void			*free_data(t_data *data);
void			*free_cmd_data(t_cmd_data *cmd_data);

// -----------------------------------------------------------------------------
// ERROR
// -----------------------------------------------------------------------------
int				ft_error(char *s);
int				ft_error_strs(char *s1, char *s2);

#endif