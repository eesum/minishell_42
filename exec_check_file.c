/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_check_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:45:05 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/20 12:56:06 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_input_file(char *file)
{
	if (access(file, F_OK) != 0)
	{
		error_msg_only("No such file or directory", file, 0);
		return (-1);
	}
	else if (access(file, R_OK) != 0)
	{
		error_msg_only("Permission denied", file, 0);
		return (-1);
	}
	return (0);
}

int	check_output_file(char *file, char mode)
{
	int	fd;

	if (mode == 'a')
	{
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
		{
			error_msg_only("Permission denied", file, 0);
			return (-1);
		}
		close(fd);
	}
	else if (mode == 't')
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			error_msg_only("Permission denied", file, 0);
			return (-1);
		}
		close(fd);
	}
	return (0);
}

int	check_file_open(t_list *pipe_tokens)
{
	t_list	*cur;

	cur = pipe_tokens;
	while (cur != NULL)
	{
		if (((t_token *)cur->content)->type == TYPE_INPUT)
			if (check_input_file(((t_token *)cur->content)->str) < 0)
				return (-1);
		if (((t_token *)cur->content)->type == TYPE_OUTPUT_A)
			if (check_output_file(((t_token *)cur->content)->str, 'a') < 0)
				return (-1);
		if (((t_token *)cur->content)->type == TYPE_OUTPUT_T)
			if (check_output_file(((t_token *)cur->content)->str, 't') < 0)
				return (-1);
		cur = cur->next;
	}
	return (0);
}
