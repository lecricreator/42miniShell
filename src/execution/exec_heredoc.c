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

void	exec_heredoc(t_redir *heredoc, t_fds *fds)
{
	char	*delimiter;
	char	*line;

	fds->std_in = dup(STDIN_FILENO);
	delimiter = heredoc->filename;
	line = NULL;
	if (pipe(fds->herepipe) == -1)
		error_handle(ERR_UNKNOWN, heredoc->filename,
			"exec_heredoc.c:24\npipe failed", KILL);
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
		error_handle(ERR_UNKNOWN, "herepipe[0]:",
			"exec_heredoc:37\ndup2 failed", KILL);
	close(fds->herepipe[0]);
	close(fds->herepipe[1]);
}
