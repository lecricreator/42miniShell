#include "minishell.h"

void    exec_heredoc(t_data *data, t_cmd *heredoc)
{
    char    *delimiter;
    char    *line;
    pid_t   herepipe[2];

    delimiter = heredoc->cmd_args[1];
    line = NULL;
    if (pipe(herepipe) == -1)
       error_handle(data, heredoc->cmd_args[0], "exec_heredoc\npipe failed", 1);
    while(1)
    {
        line = readline("> ");
        if (ft_strncmp(line, delimiter, ft_strlen(line)))
            break ;
        ft_printf_fd(herepipe[1], "%s\n", line);
        free(line);
        line = NULL;
    }
    dup2(herepipe[0], STDIN_FILENO);
    if (!herepipe[0])
        error_handle(data, "herepipe[0]", "exec_heredoc:20\ndup2 failed", 1);
    close(herepipe[0]);
    close(herepipe[1]);
}
