/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohyeki <seohyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 08:33:25 by seohyeki          #+#    #+#             */
/*   Updated: 2024/03/23 15:46:49 by seohyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

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
			exec_exit(NULL, 0);
		}
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
