/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:26:24 by odruke-s          #+#    #+#             */
/*   Updated: 2025/04/26 10:25:24 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const t_errinfo	*get_errinfo(t_error error)
{
	static t_errinfo	errtab[ERR_UNKNOWN + 1];

	errtab[ERR_SYNTAX] = (t_errinfo){ERR_SYNTAX, 2,
		"Minishell: syntax error near unexpected token `%s'\n"};
	errtab[ERR_NOT_FOUND] = (t_errinfo){ERR_NOT_FOUND, 127,
		"%s: command not found\n"};
	errtab[ERR_PERMI_OPEN] = (t_errinfo){ERR_PERMI_OPEN, 1,
		"Minishell: %s: Permission denied\n"};
	errtab[ERR_PERMI_EXEC] = (t_errinfo){ERR_PERMI_EXEC, 126,
		"Minishell: %s: Permission denied\n"};
	errtab[ERR_IS_DIRECTORY] = (t_errinfo){ERR_IS_DIRECTORY, 126,
		"Minishell: %s: Is a directory\n"};
	errtab[ERR_NO_FILE] = (t_errinfo){ERR_NO_FILE, 1,
		"Minishell: %s: No such file or directory\n"}; // is this not 127?
	errtab[ERR_NO_FILE_CD] = (t_errinfo){ERR_NO_FILE_CD, 1,
		"Minishell: cd: %s: No such file or directory\n"};
	errtab[ERR_NO_FILE_X] = (t_errinfo){ERR_NO_FILE_X, 127,
		"Minishell: %s: No such file or directory\n"};
	errtab[ERR_MANY_ARGS] = (t_errinfo){ERR_MANY_ARGS, 1,
		"Minishell: %s: too many arguments\n"};
	errtab[ERR_INVAL_IDE] = (t_errinfo){ERR_INVAL_IDE, 1,
		"Minishell: export: `%s': not a valid identifier\n"};
	errtab[ERR_UNKNOWN] = (t_errinfo){ERR_UNKNOWN, 1, "%s: %s\n"};
	return (&errtab[error]);
}

int	error_handle(t_error error, char *cmd, char *extra, int terminate)
{
	const t_errinfo	*err_info;
	t_data			*data;
	int				error_status;

	data = recover_data_address(NULL);
	err_info = get_errinfo(error);
	data->status = err_info->exit_code;
	if (!extra)
		ft_printf_fd(2, err_info->str_format, cmd);
	else
		ft_printf_fd(2, err_info->str_format, cmd, extra);
	if (terminate)
	{
		error_status = data->status;
		free_data(data);
		rl_clear_history();
		exit(error_status);
	}
	else
		return (data->status);
}
