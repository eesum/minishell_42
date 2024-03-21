/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 20:15:12 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/21 22:37:16 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_with_code(int exit_code)
{
	if (exit_code < 0)
		exit_code = 256 + (exit_code % 256);
	else if (exit_code > 255)
		exit_code = exit_code % 256;
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
		exit_with_code(255);
	}
	return (sign * result);
}

void	exec_exit(char **cmd, int pipe_flag)
{
	int	i;
	int	exit_code;

	if (pipe_flag == 0)
		printf("exit\n");
	if (cmd == NULL || cmd[1] == NULL)
		exit_with_code(EXIT_SUCCESS);
	i = 0;
	exit_code = exit_atoi(cmd);
	if (cmd[2] != NULL)
	{
		error_msg_only("too many arguments", cmd[0], 0);
		exit_code = 1;
	}
	exit_with_code(exit_code);
}
