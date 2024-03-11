/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:44:34 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/11 20:12:07 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_option(char **cmd, int *n_flag)
{
	int	i;

	if (cmd[1][0] == '-')
	{
		i = 1;
		while (cmd[1][i])
		{
			if (cmd[1][i] == 'n')
				*n_flag = 1;
			else
			{
				*n_flag = 0;
				break;
			}
			i++;
		}
	}
}

void	exec_echo(char **cmd)
{
	int	i;
	int	n_flag;

	n_flag = 0;
	if (cmd[1] != NULL)
	{
		check_option(cmd, &n_flag);
		i = 1 + n_flag;
		while (cmd[i])
		{
			printf("%s", cmd[i]);
			i++;
			if (cmd[i])
				printf(" ");
		}
		if (n_flag == 0)
			printf("\n");
	}
}
