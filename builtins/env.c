/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:51:51 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/23 21:11:41 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"
#include "../include/minishell.h"
#include <stdio.h>

static int	is_with_value(char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (content[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	exec_env(char **cmd, t_list *env)
{
	int		i;
	t_list	*cur;

	if (check_cmd_option(cmd) < 0)
		return (-1);
	i = 0;
	if (cmd[1] != NULL)
	{
		error_msg_only("not a valid argument", cmd[0], cmd[i]);
		return (-1);
	}
	cur = env;
	while (cur != NULL)
	{
		if (((char *)cur->content)[0] != '?' && \
			is_with_value((char *)cur->content) == 1)
			printf("%s\n", ((char *)cur->content));
		cur = cur->next;
	}
	return (0);
}
