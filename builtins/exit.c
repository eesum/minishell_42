/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 20:15:12 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/19 23:06:30 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_after_print(int exit_code)
{
	if (exit_code < 0)
		exit_code = 256 + (exit_code % 256);
	else if (exit_code > 255)
		exit_code = exit_code % 256;
	printf("exit\n");
	exit(exit_code);
}

int	exit_atoi(char **cmd)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	if (cmd[1][i] && (cmd[1][i] == '-' || cmd[1][i] == '+'))
	{
		if (cmd[1][i] == '-')
			sign = -1;
		i++;
	}
	while (cmd[1][i] && (cmd[1][i] >= '0' && cmd[1][i] <= '9'))
		result = result * 10 + (cmd[1][i++] - '0');
	if (cmd[1][i] != '\0' && (cmd[1][i] < '0' || cmd[1][i] > '9'))
	{
		error_msg_only("numeric argument required", cmd[0], cmd[1]);
		exit_after_print(255);
	}
	return (sign * result);
}

void	exec_exit(char **cmd)
{
	int	i;
	int	exit_code;

	if (cmd == NULL || cmd[1] == NULL)
		exit_after_print(EXIT_SUCCESS);
	i = 0;
	exit_code = exit_atoi(cmd);
	exit_after_print(exit_code);
}
