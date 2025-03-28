#include "minishell.h"

t_list  *exec_redir(t_data *data, t_list *token_list, t_fds *fds)
{
	close(fds->pipefd[0]);
    if (dup2(fds->pipefd[1], STDOUT_FILENO) == -1)
		error_handle(data, (char *)((t_token *)token_list->content)->str, "File: execution_utils || Function: exec_redir || dup2 failed", 1);

	/*next type = filename*/
}

t_list  *exec_pipe(t_data *data, t_list *token_list, t_fds *fds)
{
	close(fds->pipefd[0]);
    if (dup2(fds->pipefd[1], STDOUT_FILENO) == -1)
		error_handle(data, (char *)((t_token *)token_list->content)->str, "File: execution_utils || Function: exec_pipe || dup2 failed", 1);
	/*command*/
}

t_list  *exec_cmd(t_data *data, t_list *token_list, t_fds *fds)
{
	close(fds->pipefd[0]);
    if (dup2(fds->pipefd[1], STDOUT_FILENO) == -1)
		error_handle(data, (char *)((t_token *)token_list->content)->str, "File: execution_utils || Function: exec_cmd || dup2 failed", 1);
}
