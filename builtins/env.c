/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:51:51 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/18 14:05:34 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_env(char **cmd, t_list *env)
{
	int		i;
	int		name_len;
	char	*name;
	t_list	*cur;

	check_cmd_option(cmd);
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
