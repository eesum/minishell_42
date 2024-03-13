/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:52:58 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/13 21:26:52 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_pwd(char **cmd)
{
	char	*path;
	char	tmp[3];

	check_cmd_option(cmd);
	path = getcwd(NULL, 0);
	if (path == NULL)
		error_exit("malloc failed", 0, 0, EXIT_FAILURE);
	printf("%s\n", path);
	free(path);
	return (0);
}
