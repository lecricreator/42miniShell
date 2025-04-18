/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 15:53:11 by lomorale          #+#    #+#             */
/*   Updated: 2025/04/19 15:58:01 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_heredoc(t_data *data, t_redir *heredoc, t_fds *fds)
{
	char	*delimiter;
	char	*line;

	fds->std_in = dup(STDIN_FILENO);
	delimiter = heredoc->filename;
	line = NULL;
	if (pipe(fds->herepipe) == -1)
		error_handle(data, heredoc->filename, "exec_heredoc\npipe failed", 1);
	while (1)
	{
		line = readline("> ");
		if (!ft_strncmp(line, delimiter, ft_strlen(line)))
			break ;
		ft_printf_fd(fds->herepipe[1], "%s\n", line);
		free(line);
		line = NULL;
	}
	dup2(fds->herepipe[0], STDIN_FILENO);
	if (!fds->herepipe[0])
		error_handle(data, "herepipe[0]", "exec_heredoc:20\ndup2 failed", 1);
	close(fds->herepipe[0]);
	close(fds->herepipe[1]);
}
