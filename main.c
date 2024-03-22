/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohyeki <seohyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 08:33:25 by seohyeki          #+#    #+#             */
/*   Updated: 2024/03/22 15:39:23 by seohyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_execdata	data;
	t_parsedata	parse;

	if (argc != 1 || argv[1] != NULL)
		return (1);
	data.env = envp_to_lst(envp);
	signal(SIGINT, &parent_sig);
	signal(SIGQUIT, SIG_IGN);
	set_terminal_print_off();
	while (1)
	{
		parse.str = readline("minishell $ ");
		if (parse.str == NULL)
			exec_exit(NULL, 0);
		if (*parse.str)
		{
			add_history(parse.str);
			if (parsing(&parse, &data) == 0)
				exec(&data);
		}
		else
			free(parse.str);
	}
	return (0);
}
