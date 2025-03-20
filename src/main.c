/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:16:19 by lomorale          #+#    #+#             */
/*   Updated: 2025/03/20 10:12:32 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <termios.h>

int	main()
{
	char *test = readline("lu");
	int		i;
	i = 0;
	//tcgetattr(0,)
	//printf("%d // %s\n", argc, argv[0]);
	tput
	//printf("%s\n", test);
	while (1)
	{
		test = readline("lu");
		printf("%s\n", test);
	}
}
