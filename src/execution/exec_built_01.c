/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:37:39 by lomorale          #+#    #+#             */
/*   Updated: 2025/04/11 18:38:51 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	exec_echo_write(char **cmd_args, int flags, int i)
{
	int	n_appears;

	n_appears = 1000;
	if (flags != n_appears && i != 1)
		ft_printf_fd(1, " ");
	if (flags != -1 && cmd_args[i][0] == '-' && cmd_args[i][1] == 'n')
		flags = n_appears;
	else if (!cmd_args[i][0] == '\0')
	{
		ft_printf_fd(1, "%s", cmd_args[i]);
		flags--;
	}
	return (flags);
}

void	exec_echo(char **cmd_args)
{
	int		i;
	int		flags;

	i = 0;
	flags = 0;
	while (cmd_args[++i])
	{
		flags = exec_echo_write(cmd_args, flags, i);
	}
	if (flags <= 0)
		ft_printf_fd(1, "\n");
}

void	exec_export(char **cmd_args, t_list **env_list)
{
	char	*var_in_env_list;
	char	*new_value;
	int		i;

	i = -1;
	var_in_env_list = strdup_limiter(cmd_args[1], '=');
	if (give_var_env_list(var_in_env_list, *env_list) != NULL)
	{
		while (cmd_args[1][++i])
			if (cmd_args[1][i] == '=')
				break ;
		ft_printf_fd(1, "%s\n", &cmd_args[1][i]);
		write_env_list(&cmd_args[1][i], var_in_env_list, env_list);
	}
	else
	{
		new_value = ft_strdup(cmd_args[1]);
		if (!new_value)
			//ERROR MALLOC // EXIT WITH MESSAGE ERROR MALLOC
		ft_lstadd_back(env_list, ft_lstnew(new_value));
	}
	free(var_in_env_list);
}

void	exec_unset(char **cmd_args, t_list **env_list)
{
	char	*var_in_env_list;
	t_list	*tmp_head;
	t_list	*tmp_linked_list;

	tmp_head = *env_list;
	var_in_env_list = strdup_limiter(cmd_args[1], '=');
	if (!var_in_env_list)
		return ;
	if (give_var_env_list(var_in_env_list, *env_list))
	{
		while((*env_list)->next)
		{
			if (strncmp(cmd_args[1], (*env_list)->next->content,
				ft_strlen(cmd_args[1])) == 0)
			{
				free((*env_list)->next->content);
				tmp_linked_list = (*env_list)->next;
				(*env_list)->next = (*env_list)->next->next;
				free(tmp_linked_list);
				(*env_list) = tmp_head;
				break ;
			}
			(*env_list) = (*env_list)->next;
		}
	}
	free(var_in_env_list);
}
