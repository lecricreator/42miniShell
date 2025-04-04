/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:16:19 by lomorale          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/03/28 15:57:18 by lomorale         ###   ########.fr       */
=======
/*   Updated: 2025/04/04 10:04:50 by lomorale         ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_data *data, char **env)
{
	data->input = NULL;
	data->env_list = NULL;
	get_env(&data->env_list, env);
	data->path = NULL;
	data->token_list = NULL;
	data->cmd_list = NULL;
}

void	test(int sigtype)
{
	if (sigtype == SIGINT)
		{
			ft_putstr(1, "\n");
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
			//exit_status = 130;
		}
	else if (sigtype == SIGQUIT)
	{
		rl_redisplay();
		ft_printf_fd(1, "Ctrl + \\\n");
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;
	struct sigaction sa;

<<<<<<< HEAD
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = &test;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
=======
	(void)ac;
	(void)av;
>>>>>>> main
	data = ft_calloc(1, sizeof(t_data));
	init_data(data, env);
//	print_env(data->env_list);
	while (1)
	{
		reset_input(data);
		data->input = readline("Minishell $ ");
<<<<<<< HEAD
		if (!data->input)
			printf("exit\n");
		add_history(data->input);
		parsing(data);
		print_token_list(data->token_list);
		ft_printf_fd(2, "res : %s\n", data->input);
		if (!ft_strncmp(data->input, "exit", ft_strlen(data->input)))
=======
		add_history(data->input);
		parsing(data);
//		print_token_list(data->token_list);
		create_cmd_block(data, data->token_list);
		execution(data);
		wait(NULL);
		if (!ft_strncmp("exit", data->input, ft_strlen("exit")))
>>>>>>> main
			error_handle(data, data->input, strerror(errno), 1);
		else if (!ft_strncmp(data->token_list->content, "cd", 2))
			test_cd();
	}
}
