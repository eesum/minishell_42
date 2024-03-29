/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 08:33:25 by seohyeki          #+#    #+#             */
/*   Updated: 2024/03/29 17:36:05 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

static void	parse_n_exec(t_parsedata *parse, t_execdata *data)
{
	if (*parse->str)
	{
		if (parsing(parse, &(data->pipe), data->env) == 0)
			end_exec(data, exec(data));
		free(parse->env_str);
	}
	free(parse->str);
}

int	main(int argc, char **argv, char **envp)
{
	t_parsedata	parse;
	t_execdata	data;

	if (argc != 1 || argv[1] != NULL)
		return (1);
	data.env = envp_to_lst(envp);
	while (1)
	{
		parse.str = prompt_shell(data.env);
		if (parse.str == NULL)
			exec_exit(NULL, 0, data.env);
		parse_n_exec(&parse, &data);
	}
	return (0);
}
