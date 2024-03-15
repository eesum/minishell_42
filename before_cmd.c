/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:36:20 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/15 14:54:00 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_file_open(t_list *pipe_cntnt)
{
	t_list	*cur;
	int		fd;

	cur = pipe_cntnt;
	while (cur != NULL)
	{
		if (((t_token *)cur->content)->type == TYPE_INPUT)
		{
			if (access(((t_token *)cur->content)->str, F_OK) != 0)
			{
				error_msg_only("No such file or directory", ((t_token *)cur->content)->str, 0);
				return (-1);
			}
			else if (access(((t_token *)cur->content)->str, R_OK) != 0)
			{
				error_msg_only("Permission denied", ((t_token *)cur->content)->str, 0);
				return (-1);
			}
		}
		if (((t_token *)cur->content)->type == TYPE_OUTPUT_A)
		{
			fd = open(((t_token *)cur->content)->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
			{
				error_msg_only("Permission denied", ((t_token *)cur->content)->str, 0);
				return (-1);
			}
			close(fd);
		}
		if (((t_token *)cur->content)->type == TYPE_OUTPUT_T)
		{
			fd = open(((t_token *)cur->content)->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
			{
				error_msg_only("Permission denied", ((t_token *)cur->content)->str, 0);
				return (-1);
			}
			close(fd);
		}
		cur = cur->next;
	}
	return (0);
}

int	open_last_input(t_list *pipe, char **file_arr)
{
	t_list	*cur;
	char	*in;
	char	fd;
	int		hd_flag;

	in = NULL;
	hd_flag = 0;
	cur = pipe->content;
	while (cur != NULL)
	{
		if (((t_token *)cur->content)->redirect_flag == 1)
		{
			if (((t_token *)cur->content)->type == TYPE_INPUT)
				in = ((t_token *)cur->content)->str;
			else
				in = file_arr[((t_token *)cur->content)->hd_index];
		}
		cur = cur->next;
	}
	if (in == NULL)
		return (-1);
	fd = open(in, O_RDONLY);
	if (fd < 0)
		error_msg_only("file open failed", in, 0);
	return (fd);
}

int	open_last_output(t_list *pipe)
{
	t_list	*cur;
	char	*out;
	char	append_flag;
	char	fd;

	append_flag = 0;
	out = NULL;
	cur = pipe->content;
	while (cur != NULL)
	{
		if (((t_token *)cur->content)->redirect_flag == 2)
		{
			out = ((t_token *)cur->content)->str;
			if (((t_token *)cur->content)->type == TYPE_OUTPUT_A)
				append_flag = 1;
		}
		cur = cur->next;
	}
	if (out == NULL)
		return (-1);
	if (append_flag == 0)
		fd = open(out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(out, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		error_msg_only("file open failed", out, 0);
	return (fd);
}

void	dup_fds(t_execdata *data, int input_fd, int output_fd)
{
	if (input_fd > 0)
	{
		data->tmp_fd[0] = dup(0);
		dup2(input_fd, 0);
		close(input_fd);
	}
	if (output_fd > 0)
	{
		data->tmp_fd[1] = dup(1);
		dup2(output_fd, 1);
		close(output_fd);
	}
}
