/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:44:34 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/18 12:42:56 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	flag_echo_option(char *cmd)
{
	int	i;
	int	flag;

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
				break;
			}
			i++;
		}
	}
	return (flag);
}

int	check_echo_option(char **cmd, int *n_flag)
{
	int	i;
	int	j;

	if (flag_echo_option(cmd[1]) == 1)
		*n_flag = 1;
	i = 2;
	while (cmd[i])
	{
		if (flag_echo_option(cmd[i]) == 0)
			return (i);
		i++;
	}
	return (0);
}

int	exec_echo(char **cmd)
{
	int	i;
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
		if (n_flag == 0)
			printf("\n");
	}
	return (0);
}
