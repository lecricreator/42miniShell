/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:02:03 by lomorale          #+#    #+#             */
/*   Updated: 2025/04/06 13:25:03 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include "ft_printf.h"
# include <stdio.h>
# include <curses.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <limits.h>
# include <sys/types.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>

typedef struct s_fds
{
	int	pipefd[2];
	int	herepipe[2];
	int	prev_pipe;
	int	infile;
	int	outfile;
	int std_in;
	int std_out;
}	t_fds;

typedef enum e_type
{
	BI_ECHO,
	BI_CD,
	BI_PWD,
	BI_EXPORT,
	BI_UNSET,
	BI_ENV,
	BI_EXIT,
	OP_PIPE,
	OP_REDIR_IN,
	OP_REDIR_OUT,
	OP_APPEND,
	OP_HEREDOC,
	COMMAND,
	FILENAME,
	ARGUMENT,
	DELIMITER,
	BAD_TOKEN,
	UNKNOW,
	ENV_VAR,
	NONE
}t_type;

typedef struct s_token
{
	char	*str;
	t_type	type;
	int		index;
}t_token;

typedef struct s_redir
{
	t_type	type;
	char	*filename;
}t_redir;

typedef struct s_cmd
{
	t_type	type;
	char	**cmd_args;
	int		nbr_arg;
	char	*command_path;
	t_list	*redir;
	int		is_pipe;
}t_cmd;

typedef struct s_data
{
	t_list	*env_list;
	t_list	*token_list;
	t_list	*cmd_list;
	char	*input;
	char	**path;// should be this here??
	int		status;
	int		n_fork;
	pid_t	pid;
}t_data;

void	init_data(t_data *data, char **env);
void	parsing(t_data *data);
void	print_env(t_list *env);
int		error_handle(t_data *data, char *cmd, char *msg, int terminate);
void	free_table(char **table);
void	free_data(t_data *data);
void	free_cmd(void *cmd_void);
void	free_token(void *token_void);
void	free_list(t_list **list, void (*del)(void *));
void	free_redir(void *redir_void);
void	get_env(t_list **env_list, char **env);
char	**get_path(char **path, t_list *env);
int		count_table(char **table);
char	**get_env_tab(t_list *env_list);
void	lexing_tokens(t_data *data, char *input);
void	print_token_list(t_list *token_list);
void	reset_input(t_data *data);
void	execution(t_data *data);
void	create_cmd_block(t_data *data, t_list *token_list, t_list **cmd_list);
int		wait_and_status(t_data *data);
void	exec_redir(t_data *data, t_list *redir, t_fds *fds);
void	exec_pipe(t_data *data, t_cmd *cmd, t_fds *fds);
void	exec_cmd(t_data *data, t_cmd *cmd, t_fds *fds);
void    exec_heredoc(t_data *data, t_redir *heredoc, t_fds *fds);
void	reset_io(t_data *data, t_fds *fds);
void	change_io(t_data *data, t_redir *redir, t_fds *fds);
int		exec_pwd(void);
int		exec_cd(char *str, t_list **env_list);
void	exec_echo(char **cmd_args, t_list *env_list);
int		is_builtin(t_type type);
int		is_any_cmd(t_type type);
int		is_redir_op(t_type type);
char	*give_var_env_list(char *value, t_list *env_list);
void	write_env_list(char *old_value, char *env_value, t_list **env_list);
#endif
