#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

void	function(char *input, char **env)
{
	char *cmd[2];

	cmd[0] = strncpy(cmd[0], input, strlen(input));
	cmd[1] = NULL;
	if (!strcmp("ls", input))
		execve("/usr/bin/ls", cmd, env);
	else if (!strcmp("clear", input))
		execve("/usr/bin/clear", cmd, env);
	else
		exit(0);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char	*input;
	pid_t pid;

	input = readline("Minishell$ ");
	while(1)
	{
		input = readline("Minishell$ ");
		pid = fork();
		if (!pid)
			function(input, env);
		wait(NULL);
		if (input)
			free(input);
	}
}
