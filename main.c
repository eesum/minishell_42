/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 08:33:25 by seohyeki          #+#    #+#             */
/*   Updated: 2024/03/20 12:57:35 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(t_parsedata *parse, t_execdata *exec)
{
	parse->token_head = NULL;
	parsing_env(parse, exec->env);

	if (split_token(&(parse->token_head), parse->env_str))
	{
		error_msg_only("syntax error", 0, 0);
		free(parse->str);
		free(parse->env_str);
		return (1);
	}
	free(parse->str);
	free(parse->env_str);
	exec->pipe = NULL;
	if (parse->token_head != NULL)
	{
		if (beautify_token(&(parse->token_head), &(exec->pipe)))
		{
			error_msg_only("syntax error", 0, 0);
			return (1);
		}
	}
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	t_execdata	data;
	t_parsedata	parse;

	if (argc != 1 || argv[1] != NULL)
		return (1);
	data.env = envp_to_lst(envp);
	signal(SIGINT, &par_sig);
	signal(SIGQUIT, SIG_IGN);
	set_terminal_print_off();
	while (1)
	{
		parse.str = readline("minishell $ ");
		if (parse.str == NULL)
			exit_after_print(EXIT_SUCCESS);
		if(*parse.str)
		{
			add_history(parse.str);
			if (parsing(&parse, &data) == 0)
			{
				exec(&data);	
				ft_lstclear(&data.pipe, free_tokens_in_pipe);
			}
		}
		else
			free(parse.str);
	}
	return (0);
}
