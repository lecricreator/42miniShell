#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*res;

	if (!s1)
		return (NULL);
	if (!s2)
		return (strdup(s1));
	res = calloc((strlen(s1) + strlen(s2) + 1), sizeof(char));
	if (!res)
		return (NULL);
	strncpy(res, s1, strlen(s1) + 1);
	strncpy(res + strlen(s1), s2, strlen(s2) + 1);
	return (res);
}

void	function(char *path)
{
	if (path)
		if(!chdir(path))
			return ;
	return ;
}

char	*get_prompt(void)
{
	char	*prompt;
	char	*temp;
	char	*cwd;
	prompt = strdup("Minishell:~");
	cwd = getcwd(NULL, 0);
	temp = cwd;
	cwd = strrchr(cwd, '/');
	free(temp);
	if (cwd)
	{
		temp = prompt;
		prompt = ft_strjoin(prompt, cwd);
		free(temp);
		temp = prompt;
		prompt = ft_strjoin(prompt, "$ ");
		free(temp);
	}
	else
	{
		temp = prompt;
		prompt = ft_strjoin(prompt, "$ ");
		free(temp);
	}
	return (prompt);
}

int	main()
{
	char	*input;
	char	*prompt;

	while(1)
	{
		prompt = get_prompt();
		input = readline(prompt);
		if (!strcmp(input, "cd"))
			function("..");
		if (input)
			free(input);
		if (prompt)
			free(prompt);
	}
}
