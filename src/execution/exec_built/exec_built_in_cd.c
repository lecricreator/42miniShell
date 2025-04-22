/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in_cd.c                                  :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:35:45 by lomorale          #+#    #+#             */
/*   Updated: 2025/04/22 16:51:30 by odruke-s       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cd(t_cmd *cmd, t_list **env_list)
{
	char	buffer[1024];
	char	*old_pwd;
	int		exit_code;

	exit_code = 0;
	old_pwd = ft_strdup(getcwd(buffer, sizeof(buffer)));
	if (!cmd->cmd_args[1])
		exit_code = chdir(give_var_env_list("HOME=", *env_list));
	else if (cmd->cmd_args[1][0] == '~' && cmd->cmd_args[1][1] == '\0')
		exit_code = chdir(give_var_env_list("HOME=", (*env_list)));
	else if (cmd->cmd_args[1][0] == '-' && cmd->cmd_args[1][1] == '\0')
	{
		ft_printf_fd(1, "%s\n", give_var_env_list("OLDPWD=", (*env_list)));
		exit_code = chdir(give_var_env_list("OLDPWD=", (*env_list)));
	}
	else
		exit_code = chdir(cmd->cmd_args[1]);
	if (exit_code == -1)
		exit_code = error_handle(ERR_NO_FILE, cmd->cmd_args[1], NULL, CONTINUE);
	else
	{
		write_env_list(getcwd(buffer, sizeof(buffer)), "PWD=", env_list);
		write_env_list(old_pwd, "OLDPWD=", env_list);
	}
	return (free(old_pwd), exit_code);
}
