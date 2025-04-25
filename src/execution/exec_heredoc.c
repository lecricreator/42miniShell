/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 15:53:11 by lomorale          #+#    #+#             */
/*   Updated: 2025/04/21 22:45:19 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	here_loop(t_data *data, char *line, char *delimiter, t_fds *fds)
{
	int	exit_code;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_DFL);
	close(fds->herepipe[0]);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_printf_fd(2, "minishell: warning: here-document delimited ");
			ft_printf_fd(2, "by end-of-file (wanted `%s')\n", delimiter);
			break ;
		}
		if (!ft_strncmp(line, delimiter, ft_strlen(line) + 1))
			break ;
		ft_printf_fd(fds->herepipe[1], "%s\n", line);
		free(line);
		line = NULL;
	}
	if (line)
		free(line);
	exit_code = data->status;
	free_data(data);
	exit(exit_code);
}

void	exec_heredoc(t_redir *heredoc, t_fds *fds)
{
	t_data	*data;
	char	*delimiter;
	char	*line;

	data = recover_data_address(NULL);
	fds->std_in = dup(STDIN_FILENO);
	delimiter = heredoc->filename;
	line = NULL;
	if (pipe(fds->herepipe) == -1)
		error_handle(ERR_UNKNOWN, heredoc->filename,
			"exec_heredoc.c:56\npipe failed", KILL);
	data->pid = fork();
	if (data->pid == -1)
		error_handle(ERR_UNKNOWN, "Minishell :",
			"exec_cmd:60\nFork failed", KILL);
	data->n_fork++;
	if (!data->pid)
		here_loop(data, line, delimiter, fds);
	waitpid(data->pid, &data->status, 0);
	close(fds->herepipe[1]);
	if (dup2(fds->herepipe[0], STDIN_FILENO) == -1)
		error_handle(ERR_UNKNOWN, "herepipe[0]:",
			"exec_heredoc:68\ndup2 failed", KILL);
	close(fds->herepipe[0]);
}
