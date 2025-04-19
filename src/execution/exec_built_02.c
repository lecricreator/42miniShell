/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:37:39 by lomorale          #+#    #+#             */
/*   Updated: 2025/04/19 15:58:58 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pwd(void)
{
	char	buffer[1024];

	getcwd(buffer, sizeof(buffer));
	ft_printf_fd(1, "%s\n", buffer);
	return (errno);
}

void	exec_exit(void)
{
	t_data	*tmp_data;

	ft_printf_fd(2, "exit\n");
	tmp_data = recover_data_address(NULL);
	free_data(tmp_data);
	exit(errno);
}
/*
int	adapt_cd(t_cmd *cmd, t_list **env_list)
{
	char	buffer_pwd[1024];
	char	buffer_oldpwd[1024];
	if (!cmd->cmd_args[1])
	{
		write_env_list(getcwd(buffer_oldpwd, sizeof(buffer_oldpwd)),
			"OLDPWD=", env_list);
		chdir(give_var_env_list("HOME=", *env_list));
		write_env_list(getcwd(buffer_pwd, sizeof(buffer_pwd)),
			"PWD=", env_list);
	}
	else
		exec_cd(cmd->cmd_args[1], env_list);
	return (errno);
}
*/

int	exec_cd(t_cmd *cmd, t_list **env_list)
{
	char	buffer[1024];
	char	*old_pwd;

	old_pwd = ft_strdup(getcwd(buffer, sizeof(buffer)));
	if (!cmd->cmd_args[1])
		chdir(give_var_env_list("HOME=", *env_list));
	else if (cmd->cmd_args[1][0] == '~' && cmd->cmd_args[1][1] == '\0')
		chdir(give_var_env_list("HOME=", (*env_list)));
	else if (cmd->cmd_args[1][0] == '-' && cmd->cmd_args[1][1] == '\0')
		chdir(give_var_env_list("OLDPWD=", (*env_list)));
	else
		chdir(cmd->cmd_args[1]);
	write_env_list(old_pwd, "OLDPWD=", env_list);
	write_env_list(getcwd(buffer, sizeof(buffer)), "PWD=", env_list);
	free(old_pwd);
	return (errno);
}
