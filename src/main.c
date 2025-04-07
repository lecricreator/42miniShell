/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:16:19 by lomorale          #+#    #+#             */
/*   Updated: 2025/04/04 10:04:50 by lomorale         ###   ########.fr       */
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
	data->n_fork = 0;
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	(void)ac;
	(void)av;
	data = ft_calloc(1, sizeof(t_data));
	init_data(data, env);
//	print_env(data->env_list);
	while (1)
	{
		reset_input(data);
		data->input = readline("Minishell $ ");
		add_history(data->input);
		parsing(data);
//		print_token_list(data->token_list);
		create_cmd_block(data, data->token_list);
		execution(data);
		wait_and_status(data);
		if (!ft_strncmp("exit", data->input, ft_strlen("exit")))
			error_handle(data, data->input, strerror(errno), 1);
	}
}
