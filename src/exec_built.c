/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:37:39 by lomorale          #+#    #+#             */
/*   Updated: 2025/04/06 10:46:50 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char	*give_var_linked_list(char *value, t_list *env_list)
{
	char	*tmp_content;
	int		size_value;

	size_value = (int)ft_strlen(value);
	while (env_list)
	{
		tmp_content = (env_list)->content;
		if (ft_strncmp(value, tmp_content, size_value) == 0)
			break ;
		env_list = env_list->next;
	}
	return (&tmp_content[size_value + 1]);
}

void	write_env_list(char *old_value, char *env_value, t_list **env_list)
{
	char	*tmp_content;
	t_list	*head_env;
	int		size_value;

	head_env = (*env_list);
	size_value = (int)ft_strlen(env_value);
	while ((*env_list))
	{
		tmp_content = (*env_list)->content;
		if (ft_strncmp(env_value, tmp_content, size_value) == 0)
			break ;
		(*env_list) = (*env_list)->next;
	}
	(*env_list)->content = ft_strjoin(env_value, old_value);
	(*env_list) = head_env;
}

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
		chdir(give_var_linked_list("HOME", (*env_list)));
	}
	else if (str[0] == '-' && str[1] == '\0')
	{
		chdir(give_var_linked_list("OLDPWD", (*env_list)));
	}
	else
	{
		write_env_list(getcwd(buffer, sizeof(buffer)), "OLDPWD=", env_list);
		chdir(str);
	}
	write_env_list(getcwd(buffer, sizeof(buffer)), "PWD=", env_list);
	return (errno);
}

void	exec_echo(char **cmd_args, t_list *env_list)
{
	int		i;
	int		flags;

	i = 0;
	flags = 0;
	while(cmd_args[++i])
	{
		if (cmd_args[i][0] == '$')
		{
			ft_printf_fd(1, "%s\n", give_var_linked_list(&cmd_args[i][1],
				env_list));
			flags = -1;
		}
		else if (flags != -1 && cmd_args[i][0] == '-' && cmd_args[i][1] == 'n')
			flags++;
		else if (!cmd_args[i][0] == '\0')
		{
			ft_printf_fd(1, "%s", cmd_args[i]);
			flags = -1;
		}
	}
	if (flags <= 0)
		ft_printf_fd(1, "\n", cmd_args);
}
