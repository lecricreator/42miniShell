/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:37:39 by lomorale          #+#    #+#             */
/*   Updated: 2025/04/04 15:43:21 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char	*give_var_linked_list(char *value, t_list **env_list)
{
	char	*tmp_content;
	int		size_value;

	size_value = (int)ft_strlen(value);
	while (env_list)
	{
		tmp_content = *(env_list)->content;
		if (ft_strncmp(value, tmp_content, size_value) == 0)
			break ;
		env_list = env_list->next;
	}
	return (&tmp_content[size_value + 1]);
}

void	write_env_list(char *old_value, char *env_value, t_list *env_list)
{
	char	*tmp_content;
	int		size_value;

	size_value = (int)ft_strlen(env_value);
	while (env_list)
	{
		tmp_content = env_list->content;
		if (ft_strncmp(env_value, tmp_content, size_value) == 0)
			break ;
		env_list = env_list->next;
	}
	tmp_content = ft_strjoin(env_value, old_value);
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

	write_env_list(getcwd(buffer, sizeof(buffer)), "OLDPWD=", env_list);
	if (str[0] == '~' && str[1] == '\0')
	{
		chdir(give_var_linked_list("HOME", env_list));
	}
	if (str[0] == '-' && str[1] == '\0')
	{
		chdir(give_var_linked_list("OLDPWD", env_list));
	}
	else
		chdir(str);
	write_env_list(getcwd(buffer, sizeof(buffer)), "PWD=", env_list);
	return (errno);
}

int	exec_echo(char *str, t_list *env_list)
{
	(void)env_list;
	if (str[0] == '$')
	{

	}
	else
	{
		ft_printf_fd(1, "%s\n", str);
	}
	return (1);
}
