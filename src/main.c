/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:16:19 by lomorale          #+#    #+#             */
/*   Updated: 2025/03/28 11:23:42 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	init_data(t_data *data, char **env)
{
	data->input = NULL;
	data->env_list = NULL;
	get_env(&data->env_list, env);
	data->token_list = NULL;
}

void	test(int sigtype)
{
	if (sigtype == SIGINT)
		ft_printf_fd(1, "Ctrl + C %d\n", sigtype);
	else if (sigtype == SIGQUIT)
	{
		ft_printf_fd(1, "Annule commande CTR + \\ %d\n", sigtype);
		readline("Minishell $ ");
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_data	*data;
	struct sigaction sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = &test;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	data = ft_calloc(1, sizeof(t_data));
	init_data(data, env);
//	print_env(data->env_list);
	while (1)
	{
		reset_input(data);
		data->input = readline("Minishell $ ");
		if (!data->input)
			printf("exit\n");
		add_history(data->input);
		parsing(data);
		print_token_list(data->token_list);
		ft_printf_fd(2, "res : %s\n", data->input);
		if (!ft_strncmp(data->input, "exit", ft_strlen(data->input)))
			error_handle(data, data->input, strerror(errno), 1);
		else if (!ft_strncmp(data->token_list->content, "cd", 2))
			test_cd();
	}
}
