/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:52:58 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/23 17:45:08 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"
#include "../include/minishell.h"
#include <stdio.h>

int	exec_pwd(char **cmd)
{
	char	*path;

	if (check_cmd_option(cmd) < 0)
		return (-1);
	path = getcwd(NULL, 0);
	if (path == NULL)
		error_exit("malloc failed", 0, 0, EXIT_FAILURE);
	printf("%s\n", path);
	free(path);
	return (0);
}
