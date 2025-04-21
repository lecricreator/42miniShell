/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:26:24 by odruke-s          #+#    #+#             */
/*   Updated: 2025/04/18 20:20:20 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const t_errinfo	*get_errinfo(t_error error)
{
	static t_errinfo	errtab[ERR_UNKNOWN + 1];

	errtab[ERR_SYNTAX] = (t_errinfo){ERR_SYNTAX, 2, "Minishell: syntax error near `%s'\n"};
	errtab[ERR_NOT_FOUND] = (t_errinfo){ERR_NOT_FOUND, 127, "%s: command not found\n"};
	errtab[ERR_PERMISSION] = (t_errinfo){ERR_PERMISSION, 126, "Minishell: %s: permission denied\n"};
	errtab[ERR_IS_DIRECTORY] = (t_errinfo){ERR_IS_DIRECTORY, 126, "Minishell: %s: is a directory\n"};
	errtab[ERR_NO_FILE] = (t_errinfo){ERR_NO_FILE, 1, "Minishell: %s: No such file or directory\n"};
	errtab[ERR_MANY_ARGS] = (t_errinfo){ERR_MANY_ARGS, 1, "Minishell: %s:too many arguments\n"};
	errtab[ERR_INVAL_IDE] = (t_errinfo){ERR_INVAL_IDE, 1, "Minishell: `%s': not a valid identifier\n"};
	errtab[ERR_UNKNOWN] = (t_errinfo){ERR_UNKNOWN, 1, "%s: %s\n"};
	return (&errtab[error]);
}

int	error_handle(t_error error, char *cmd, char *extra, int terminate)
{
	const t_errinfo	*err_info;
	t_data		*data;

	data = recover_data_address(NULL);
	err_info = get_errinfo(error);
	data->status = err_info->exit_code;
	if (!extra)
		ft_printf_fd(2, err_info->str_format, cmd);
	else
		ft_printf_fd(2, err_info->str_format, cmd, extra);
	if (terminate)
	{
		free_data(data);
		rl_clear_history();
		exit(data->status);
	}
	else
		return (data->status);
}
/*
int	error_handle_without_rl(t_data *data, char *cmd, char *msg, int terminate)
{
	int	exit_code;

	if (!data)
		data = recover_data_address(NULL);
	exit_code = 1;
	ft_printf_fd(2, "%s: %s\n", cmd, msg);
	if (ft_strnstr(msg, "directory", ft_strlen(msg)) || ft_strnstr(msg,
			"permission", ft_strlen(msg)))
		exit_code = 126;
	else if (ft_strnstr(msg, "command", ft_strlen(msg)))
		exit_code = 127;
	if (terminate)
	{
		free_data(data);
		rl_clear_history();
		exit(exit_code);
	}
	else
		return (exit_code);
}

int	error_handle(t_data *data, char *cmd, char *msg, int terminate)
{
	int	exit_code;

	if (!data)
		data = recover_data_address(NULL);
	exit_code = 1;
	ft_printf_fd(2, "Minishell: %s: %s\n", cmd, msg);
	if (ft_strnstr(msg, "directory", ft_strlen(msg)) || ft_strnstr(msg,
			"permission", ft_strlen(msg)))
		exit_code = 126;
	else if (ft_strnstr(msg, "command", ft_strlen(msg)))
		exit_code = 127;
	if (terminate)
	{
		free_data(data);
		rl_clear_history();
		exit(exit_code);
	}
	else
		return (exit_code);
}*/
