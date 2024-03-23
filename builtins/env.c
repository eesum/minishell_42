/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:51:51 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/23 17:19:34 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin.h"
#include "../minishell.h"
#include <stdio.h>

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
		if (((char *)cur->content)[0] != '?')
			printf("%s\n", ((char *)cur->content));
		cur = cur->next;
	}
	return (0);
}
