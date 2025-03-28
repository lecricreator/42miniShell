/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:16:19 by lomorale          #+#    #+#             */
/*   Updated: 2025/03/27 12:02:34 by lomorale         ###   ########.fr       */
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

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	init_data(data, env);
//	print_env(data->env_list);
	while (1)
	{
		reset_input(data);
		data->input = readline("Minishell $ ");
		parsing(data);
		print_token_list(data->token_list);
		execution(data);
		if (!ft_strncmp(data->input, "exit", ft_strlen(data->input)))
			error_handle(data, data->input, strerror(errno), 1);
	}
}
