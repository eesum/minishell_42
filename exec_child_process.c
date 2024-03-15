/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:32:08 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/15 14:56:47 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	input_fd(t_execdata *data, int i)
{
	int	file_fd;
	t_list	*cur_pipe;

	cur_pipe = ft_findlst_by_index(data->pipe, i);
	file_fd = open_last_input(cur_pipe, data->file_arr);
	if (file_fd < 0)
	{
		if (i == 0)
			return (-1);
		else
			return (data->fd[(i + 1) % 2][0]);
	}
	return (file_fd);
}

int	output_fd(t_execdata *data, int i)
{
	int	file_fd;
	t_list	*cur_pipe;

	cur_pipe = ft_findlst_by_index(data->pipe, i);
	file_fd = open_last_output(cur_pipe);
	if (file_fd < 0)
	{
		if (i == data->pipe_cnt - 1)
			return (-1);
		else
			return (data->fd[i % 2][1]);
	}
	return (file_fd);
}

void	exec_in_child(t_execdata *data, int i)
{
	int	in_fd;
	int	out_fd;
	char	**cmd;
	t_list	*cur_pipe;

	cur_pipe = ft_findlst_by_index(data->pipe, i);
	if (data->index < data->pipe_cnt - 1)
		close(data->fd[i % 2][0]);
	in_fd = input_fd(data, i);
	out_fd = output_fd(data, i);
	dup_fds(data, in_fd, out_fd);
	cmd = cmd_to_arr(cur_pipe);
	exec_cmd(cmd, data->env);
}