/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:44:34 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/26 01:23:02 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <stdio.h>

static int	flag_echo_option(char *cmd)
{
	int	i;
	int	flag;

	flag = 0;
	if (cmd[0] == '-')
	{
		i = 1;
		while (cmd[i])
		{
			if (cmd[i] == 'n')
				flag = 1;
			else
			{
				flag = 0;
				break ;
			}
			i++;
		}
	}
	return (flag);
}

static int	check_echo_option(char **cmd, int *n_flag)
{
	int	i;

	if (flag_echo_option(cmd[1]) == 0)
		return (1);
	*n_flag = 1;
	i = 2;
	while (cmd[i])
	{
		if (flag_echo_option(cmd[i]) == 0)
			return (i);
		i++;
	}
	return (i);
}

int	exec_echo(char **cmd)
{
	int	n_flag;
	int	content_index;

	n_flag = 0;
	if (cmd[1] != NULL)
	{
		content_index = check_echo_option(cmd, &n_flag);
		while (cmd[content_index])
		{
			printf("%s", cmd[content_index]);
			content_index++;
			if (cmd[content_index])
				printf(" ");
		}
	}
	if (n_flag == 0)
		printf("\n");
	return (0);
}
