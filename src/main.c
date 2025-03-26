/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:16:19 by lomorale          #+#    #+#             */
/*   Updated: 2025/03/25 22:06:31 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	init_data(t_data *data, char **env)
{
	data->input = NULL;
	data->env = NULL;
	get_env(&data->env, env);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_data *data;

	data = ft_calloc(1, sizeof(t_data));
	init_data(data, env);
	print_env(data->env);
	while (1)
	{
		data->input = readline("Minishell $ ");
	//	parsing(data);
		if (!data->input)
			error_handle(data, data->input, strerror(errno), 0);
	}
}
