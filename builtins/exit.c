/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 20:15:12 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/18 14:05:49 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_after_print(int exit_code)
{
	char	*exit_code_char;

	exit_code_char = ft_itoa_err(exit_code);
	printf("exit\n");
	exit(exit_code);
}

void	exec_exit(char **cmd)
{
	int	i;
	int	exit_code;

	if (cmd[1] == NULL)
		exit_after_print(EXIT_SUCCESS);
	i = 0;
	while (cmd[1][i])
	{
		if (cmd[1][i] < 48 || cmd[1][i] > 57)
		{
			error_msg_only("numeric argument required", cmd[0], cmd[1]);
			exit_after_print(EXIT_FAILURE);
		}
		i++;
	}
	exit_code = ft_atoi(cmd[1]);
	exit_after_print(exit_code);
}
