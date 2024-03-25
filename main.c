/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 08:33:25 by seohyeki          #+#    #+#             */
/*   Updated: 2024/03/25 21:08:03 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/parse.h"
#include "include/builtin.h"
#include "include/exec.h"
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
		parse.str = readline("minishell $ \033[s");
		if (parse.str == NULL)
		{
			printf("\033[u");
			exec_exit(NULL, 0, data.env);
		}
		add_history(parse.str);
		if (parsing(&parse, &data) == 0)
			exec(&data);
		free(parse.str);
		free(parse.env_str);
	}
	return (0);
}
