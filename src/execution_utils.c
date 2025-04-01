#include "minishell.h"

t_list  *exec_redir(t_data *data, t_list *token_list, t_fds *fds)
{
	fds->prev_pipe= fds->pipefd[0];
    if (dup2(fds->pipefd[1], STDOUT_FILENO) == -1)
		error_handle(data, (char *)((t_token *)token_list->content)->str, "File: execution_utils || Function: exec_redir || dup2 failed", 1);

	/*next type = filename*/
	return (token_list->next);
}

t_list  *exec_pipe(t_data *data, t_list *token_list, t_fds *fds)
{
	close(fds->pipefd[0]);
    if (dup2(fds->pipefd[1], STDOUT_FILENO) == -1)
		error_handle(data, (char *)((t_token *)token_list->content)->str, "File: execution_utils || Function: exec_pipe || dup2 failed", 1);
	/*command*/
	return (token_list->next);
}

static int	cmd_tab_len(t_list *token_list)
{
	t_list	*tmp_head;
	t_token	*tmp_token;
	int		i;

	tmp_head = token_list;
	tmp_token = (t_token *)tmp_head->content;
	while (tmp_head && (tmp_token->type <= 6 && tmp_token->type >= 12))
	{
		i++;
		tmp_head = tmp_head->next;
	}
	return (i);
}

/*extracts the currend command and his arguments into a 2D array, 
and sets the head of the token_list to the next operator, or the end of the command line*/
static char  **get_cmd_tab(t_data *data, t_list **token_list)
{
	char	**cmd_tab;
	int		i;

	t_token	*tmp_token;

	i = 0;
	cmd_tab = ft_calloc(sizeof(char *), cmd_tab_len(*token_list) + 1);
	if (!cmd_tab)
		error_handle(data, "cmd_tab", "File: execution_utils || Function: get_cmd_tab || ft_calloc failed", 1);
	tmp_token = (t_token *)(*token_list)->content;
	while (*token_list && !(tmp_token->type >= 7 && tmp_token->type <= 11)) // while there's still arguments and token is not pipe
	{
		cmd_tab[i++] = tmp_token->str;
		*token_list = (*token_list)->next;
		if (*token_list)
			tmp_token = (t_token *)(*token_list)->content;
	}
	return (cmd_tab);
}

int	cmd_if_absolute_path(t_data *data, char **cmd_tab)
{
	errno = 0;
	data->command_path = ft_strdup(cmd_tab[0]);
	if (!access(data->command_path, X_OK))
		return (0);
	else
		return (1);
}


void	find_program(t_data *data, t_list **token_list)
{
	int		i;

	i = 0;
	data->path = get_path(data->path, data->env_list);
	data->cmd_tab = get_cmd_tab(data, token_list);
	if (ft_strchr(data->cmd_tab[0], '/'))
	{
		if (!cmd_if_absolute_path(data, data->cmd_tab))
			return ;
		else
		{
			error_handle(data, data->cmd_tab[0], "directory not found", 0);
			return ;
		}
	}
	while (data->path[i])
	{
		data->command_path = ft_strjoin(data->path[i], data->cmd_tab[0]);
		if (!access(data->command_path, X_OK))
			return ;
		free(data->command_path);
		data->command_path = NULL;
		i++;
	}
	error_handle(data,
			data->cmd_tab[0], "command not found", 0);
}

int		env_size(t_list *env_list)
{
	t_list *tmp_head;
	int	i;

	i = 0;
	tmp_head = env_list;
	while (tmp_head)
	{
		i++;
		tmp_head = tmp_head->next;
	}
	return (i);
}

char	**get_env_tab(t_list *env_list)
{
	t_list *tmp_head;
	char	**env_tab;
	int		i;

	i = 0;
	tmp_head = env_list;
	env_tab = (char **)malloc(sizeof(char *) * (env_size(env_list) + 1));
	if (!env_tab)
		error_handle(NULL, "env_tab function", "file execution_utils.c", 1); // change this line
	while (tmp_head)
	{
		env_tab[i++] = ft_strdup((char *)env_list->content);
		tmp_head = tmp_head->next;
	}
	return (env_tab);
}

int	handle_procesess(t_data *data, t_fds *fds, char **env_tab)
{
	errno = 0;
	if (!data->cmd_tab[0])
		error_handle(data, "", "permission denied", 1);
	else if (!data->command_path)
	{
		free_data(data);
		exit(127);
	}
	else if (fds->prev_pipe < 1)
	{
		free_data(data);
		exit(0);
	}
	close(fds->pipefd[0]);
	if (dup2(fds->prev_pipe, STDIN_FILENO) == -1)
		error_handle(data, "", "Error:\ndup2 failed", 1);
	if (dup2(fds->pipefd[1], STDOUT_FILENO) == -1)
		error_handle(data, "", "Error:\ndup2 failed", 1);
	close(fds->prev_pipe);
	close(fds->pipefd[1]);
	execve(data->command_path, data->cmd_tab, env_tab);
	free_table(env_tab);
	error_handle(data, data->cmd_tab[0], strerror(errno), 1);
	return (0);
}

void	exec_cmd(t_data *data, t_list **token_list, t_fds *fds)
{

	char	**env_tab;

	env_tab = get_env_tab(data->env_list);
	find_program(data, token_list);
	data->pid = fork();
	if (data->pid == -1)
		error_handle(data, "", "Error:\nFork failed", 1);
	if (!data->pid)
		handle_procesess(data, fds, env_tab);
}
