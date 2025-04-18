/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:37:39 by lomorale          #+#    #+#             */
/*   Updated: 2025/04/18 22:19:06 by lomorale         ###   ########.fr       */
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

void	exec_exit()
{
	t_data	*tmp_data;

	ft_printf_fd(2, "exit\n");
	tmp_data = recover_data_address(NULL);
	free_data(tmp_data);
	exit(errno);
}

int	adapt_cd(t_cmd *cmd, t_list **env_list)
{
	char	buffer[1024];

	if (cmd->nbr_arg <= 1)
	{
		write_env_list(getcwd(buffer, sizeof(buffer)), "OLDPWD=", env_list);
		chdir(give_var_env_list("HOME", *env_list));
		write_env_list(getcwd(buffer, sizeof(buffer)), "PWD=", env_list);
	}
	else if (cmd->nbr_arg <= 2)
		exec_cd(cmd->cmd_args[1], env_list);
	else
		error_handle(NULL, cmd->cmd_args[0], "too many arguments", 0);
	return (errno);
}

int	exec_cd(char *str, t_list **env_list)
{
	char	buffer[1024];

	if (str[0] == '~' && str[1] == '\0')
	{
		write_env_list(getcwd(buffer, sizeof(buffer)), "OLDPWD=", env_list);
		chdir(give_var_env_list("HOME", (*env_list)));
	}
	else if (str[0] == '-' && str[1] == '\0')
	{
		write_env_list(getcwd(buffer, sizeof(buffer)), "OLDPWD=", env_list);
		chdir(give_var_env_list("OLDPWD", (*env_list)));
	}
	else
	{
		write_env_list(getcwd(buffer, sizeof(buffer)), "OLDPWD=", env_list);
		chdir(str);
	}
	write_env_list(getcwd(buffer, sizeof(buffer)), "PWD=", env_list);
	return (errno);
}
