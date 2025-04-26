/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:21:52 by odruke-s          #+#    #+#             */
/*   Updated: 2025/04/25 23:28:02 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_stdin(t_fds *fds)
{
	if (fds->infile != -1 || fds->std_in != -1 || fds->herepipe[0] != -1)
	{
		if (dup2(fds->std_in, STDIN_FILENO) < 0)
			error_handle(ERR_UNKNOWN, "std in", "in_out_utils.c:21\n", KILL);
		if (fds->std_in > -1)
			close(fds->std_in);
		if (fds->infile > -1)
			close(fds->infile);
		fds->std_in = -1;
		fds->infile = -1;
	}
}

void	restore_stdout(t_fds *fds)
{
	if (fds->outfile != -1 || fds->std_out != -1)
	{
		if (dup2(fds->std_out, STDOUT_FILENO) < 0)
			error_handle(ERR_UNKNOWN, "std out",
				"in_out_utils.c:38\ndup2 failed", KILL);
		if (fds->std_out > -1)
			close(fds->std_out);
		if (fds->outfile > -1)
			close(fds->outfile);
		fds->std_out = -1;
		fds->outfile = -1;
	}
}
