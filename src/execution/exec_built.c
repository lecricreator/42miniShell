/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:37:39 by lomorale          #+#    #+#             */
/*   Updated: 2025/04/06 17:09:44 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pwd(void)
{
	char	buffer[1024];

	getcwd(buffer, sizeof(buffer));
	printf("%s\n", buffer);
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
		chdir(give_var_env_list("OLDPWD", (*env_list)));
	}
	else if (str[0] == '$')
	{
		chdir(give_var_env_list(&str[1], (*env_list)));
	}
	else
	{
		write_env_list(getcwd(buffer, sizeof(buffer)), "OLDPWD=", env_list);
		chdir(str);
	}
	write_env_list(getcwd(buffer, sizeof(buffer)), "PWD=", env_list);
	return (errno);
}

int	exec_echo_write(char **cmd_args, t_list *env_list, int flags, int i)
{
	int	n_appears;

	n_appears = 1000;
	if (flags != n_appears && i != 1)
		ft_printf_fd(1, " ");
	if (cmd_args[i][0] == '$')
	{
		ft_printf_fd(1, "%s", give_var_env_list(&cmd_args[i][1],
				env_list));
		flags--;
	}
	else if (flags != -1 && cmd_args[i][0] == '-' && cmd_args[i][1] == 'n')
		flags = n_appears;
	else if (!cmd_args[i][0] == '\0')
	{
		ft_printf_fd(1, "%s", cmd_args[i]);
		flags--;
	}
	return (flags);
}

void	exec_echo(char **cmd_args, t_list *env_list)
{
	int		i;
	int		flags;

	i = 0;
	flags = 0;
	while (cmd_args[++i])
	{
		flags = exec_echo_write(cmd_args, env_list, flags, i);
	}
	if (flags <= 0)
		ft_printf_fd(1, "\n", cmd_args);
}

void	exec_export(char **cmd_args, t_list **env_list)
{
	char	*var_in_env_list;
	int		i;

	i = -1;
	while (cmd_args[1][++i])
	{
		if (cmd_args[1][i - 1] == '=')
			break ;
	}
	var_in_env_list = calloc(1, 1 + i);
	i = -1;
	while (cmd_args[1][++i])
	{
		if (cmd_args[1][i - 1] == '=')
			break ;
		else
			var_in_env_list[i] = cmd_args[1][i];
	}
	// ft_printf_fd(2, "var env : %s\n", var_in_env_list);
	// ft_printf_fd(2, "args : %s\n", cmd_args[1]);
	(void)env_list;
	write_env_list(&cmd_args[1][i], var_in_env_list, env_list);
}
