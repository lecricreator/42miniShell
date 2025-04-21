/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:16:19 by lomorale          #+#    #+#             */
/*   Updated: 2025/04/19 15:43:09 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*recover_data_address(t_data *data)
{
	static t_data	*stock_data;

	if (data)
	{
		stock_data = data;
	}
	else
	{
		data = stock_data;
	}
	return (stock_data);
}

void	init_data(t_data *data, char **env)
{
	data->input = NULL;
	data->env_list = NULL;
	get_env(&data->env_list, env);
	data->token_list = NULL;
	data->cmd_list = NULL;
	data->n_fork = 0;
	data->status = 0;
	data->pid = 0;
	recover_data_address(data);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	(void)ac;
	(void)av;
	data = ft_calloc(1, sizeof(t_data));
	init_data(data, env);
	sig_init();
//	print_env(data->env_list);
	while (1)
	{
		reset_input(data);
		data->input = readline("Minishell $ ");
		if (!data->input)
			exec_exit();
		add_history(data->input);
		parsing(data);
//		print_token_list(data->token_list);
		create_cmd_block(data->token_list, &data->cmd_list);
		execution(data);
		wait_and_status(data);
	}
}
