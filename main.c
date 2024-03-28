/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohyeki <seohyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 08:33:25 by seohyeki          #+#    #+#             */
/*   Updated: 2024/03/28 15:49:55 by seohyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(int argc, char **argv, char **envp)
{
	t_execdata	data;
	t_parsedata	parse;

	if (argc != 1 || argv[1] != NULL)
		return (1);
	data.env = envp_to_lst(envp);
	set_sig_term(parent_sig, SIG_IGN, 0);
	while (1)
	{
		parse.str = readline("minishell $ \001\033[s\002");
		if (parse.str == NULL)
		{
			printf("\033[u");
			exec_exit(NULL, 0, data.env);
		}
		if (*parse.str)
		{
			add_history(parse.str);
			if (parsing(&parse, &(data.pipe), data.env) == 0)
				end_exec(&data, exec(&data));
			free(parse.env_str);
		}
		free(parse.str);
	}
	return (0);
}
