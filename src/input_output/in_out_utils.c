/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:21:52 by odruke-s          #+#    #+#             */
/*   Updated: 2025/04/23 16:26:11 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_stdin(t_fds *fds)
{
	if (fds->infile != -1 || fds->std_in != -1)
	{
		dup2(fds->std_in, STDIN_FILENO);
		if (fds->std_in < 0)
			error_handle(ERR_UNKNOWN, "std in", "in_out_management.c:\n", KILL);
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
		dup2(fds->std_out, STDOUT_FILENO);
		if (fds->std_out < 0)
			error_handle(ERR_UNKNOWN, "std out",
				"in_out_manage.c:21\ndup2 failed", KILL);
		if (fds->std_out > -1)
			close(fds->std_out);
		if (fds->outfile > -1)
			close(fds->outfile);
		fds->std_out = -1;
		fds->outfile = -1;
	}
}
