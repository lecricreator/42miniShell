/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 01:32:13 by odruke-s          #+#    #+#             */
/*   Updated: 2025/04/24 11:38:29 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_if_absolute_path(t_cmd *cmd)
{
	errno = 0;
	cmd->command_path = ft_strdup(cmd->cmd_args[0]);
	if (!access(cmd->command_path, F_OK))
	{
		if (!access(cmd->command_path, X_OK))
			return (0);
		else
			return (error_handle(ERR_PERMI_EXEC,
					cmd->cmd_args[0], NULL, CONTINUE));
	}
	else
		return (error_handle(ERR_NO_FILE_X,
				cmd->cmd_args[0], NULL, CONTINUE));
}

int	verif_access(char **path, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (path[i])
	{
		cmd->command_path = ft_strjoin(path[i], cmd->cmd_args[0]);
		if (!access(cmd->command_path, F_OK))
		{
			if (!access(cmd->command_path, X_OK))
				return (free_table(path), 0);
			else
				return (free_table(path), error_handle(ERR_PERMI_EXEC,
						cmd->cmd_args[0], NULL, CONTINUE));
		}
		free(cmd->command_path);
		cmd->command_path = NULL;
		i++;
	}
	return (free_table(path), error_handle(ERR_NOT_FOUND,
			cmd->cmd_args[0], NULL, CONTINUE));
}

int	find_program(t_data *data, t_cmd *cmd)
{
	char		**path;
	struct stat	st;

	path = NULL;
	path = get_path(path, data->env_list);
	if (ft_strchr(cmd->cmd_args[0], '/'))
	{
		if (stat(cmd->cmd_args[0], &st) == 0 && S_ISDIR(st.st_mode))
			return (free_table(path), error_handle(ERR_IS_DIRECTORY,
					cmd->cmd_args[0], NULL, CONTINUE));
		return (free_table(path), cmd_if_absolute_path(cmd));
	}
	if (path)
		return (verif_access(path, cmd));
	else
		return (free_table(path), error_handle(ERR_NO_FILE,
				cmd->cmd_args[0], NULL, CONTINUE));
}

int	handle_procesess(t_data *data, t_cmd *cmd, t_fds *fds, char **env_tab)
{
	errno = 0;
	if (!cmd->cmd_args[0])
		error_handle(ERR_PERMI_EXEC, "", NULL, KILL);
	else if (!cmd->command_path)
	{
		free_data(data);
		exit(127);
	}
	exec_pipe(cmd, fds);
	if (execve(cmd->command_path, cmd->cmd_args, env_tab) == -1)
	{
		free_table(env_tab);
		return (error_handle(ERR_NOT_FOUND, cmd->cmd_args[0],
				NULL, KILL));
	}
	return (errno);
}

void	exec_cmd(t_data *data, t_cmd *cmd, t_fds *fds, char **tmp_var)
{
	char	**env_tab;

	if (find_program(data, cmd))
		return ;
	env_tab = get_env_tab(data->env_list, tmp_var);
	data->pid = fork();
	if (data->pid == -1)
		error_handle(ERR_UNKNOWN, "Minishell :",
			"exec_cmd:103\nFork failed", KILL);
	data->n_fork++;
	if (!data->pid)
	{
		signal(SIGQUIT, SIG_DFL);
		handle_procesess(data, cmd, fds, env_tab);
	}
	if (env_tab)
		free_table(env_tab);
	if (tmp_var)
		free_table(tmp_var);
}
