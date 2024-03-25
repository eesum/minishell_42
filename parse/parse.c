/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:34:52 by seohyeki          #+#    #+#             */
/*   Updated: 2024/03/25 21:07:45 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

int	parsing(t_parsedata *parse, t_execdata *exec)
{
	parse->token_head = NULL;
	parsing_env(parse, exec->env);
	if (split_token(&(parse->token_head), parse->env_str))
	{
		error_msg_only("syntax error", 0, 0);
		update_env("?", "258", exec->env);
		return (1);
	}
	exec->pipe = NULL;
	if (parse->token_head != NULL)
	{
		if (beautify_token(&(parse->token_head), &(exec->pipe)))
		{
			error_msg_only("syntax error", 0, 0);
			update_env("?", "258", exec->env);
			return (1);
		}
	}
	return (0);
}
