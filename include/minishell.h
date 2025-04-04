/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:02:03 by lomorale          #+#    #+#             */
/*   Updated: 2025/04/04 18:23:04 by lomorale         ###   ########.fr       */
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
# include <errno.h>

typedef struct s_fds
{
	int	pipefd[2];
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
	BAD_TOKEN,
	UNKNOW,
	NONE
} 	t_type;

typedef struct s_token
{
	char	*str;
	t_type	type;
	int		index;
}	t_token;

typedef struct s_redir
{
	t_type	type;
	char	*filename;
}	t_redir;

typedef struct s_cmd
{
	t_type	type;
	char	**cmd_args;
	char	*command_path;
	t_list	*redir;
	int		is_pipe;
}	t_cmd;

typedef struct s_data
{
	t_list	*env_list;
	t_list	*token_list;
    char    *input;
}	t_data;

void	init_data(t_data *data, char **env);
void    parsing(t_data *data);
void    print_env(t_list *env);
int	    error_handle(t_data *data, char *cmd, char *msg, int terminate);
void    get_env(t_list **env_list, char **env);
void	lexing_tokens(t_data *data, char *input);
void	print_token_list(t_list *token_list);
void	reset_input(t_data *data);

#endif
