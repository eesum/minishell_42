/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:32:08 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/23 14:54:05 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	input_fd(t_execdata *data, t_list *cur_pipe, int i)
{
	int	file_fd;

	file_fd = open_last_input(cur_pipe, data->file_arr);
	if (file_fd < 0)
	{
		if (i == 0)
			return (-1);
		else
			return (data->fd[(i + 1) % 2][0]);
	}
	else if (i != 0)
		close(data->fd[(i + 1) % 2][0]);
	return (file_fd);
}

static int	output_fd(t_execdata *data, t_list *cur_pipe, int i)
{
	int	file_fd;

	file_fd = open_last_output(cur_pipe);
	if (file_fd < 0)
	{
		if (i == data->pipe_cnt - 1)
			return (-1);
		else
			return (data->fd[i % 2][1]);
	}
	else if (i != data->pipe_cnt - 1)
		close(data->fd[i % 2][1]);
	return (file_fd);
}

void	exec_in_child(t_execdata *data, int i)
{
	t_list	*cur_pipe;
	int		input;
	int		output;
	char	**cmd;

	cur_pipe = ft_findlst_by_index(data->pipe, i);
	cmd = cmd_to_arr(cur_pipe->content);
	if (cmd == NULL)
		exit(EXIT_SUCCESS);
	if (check_file_open(cur_pipe->content) < 0)
		exit(EXIT_FAILURE);
	if (data->index < data->pipe_cnt - 1)
		close(data->fd[i % 2][0]);
	input = input_fd(data, cur_pipe, i);
	output = output_fd(data, cur_pipe, i);
	dup_fds(data, input, output);
	exec_cmd(cmd, data->env, 1);
	exit(EXIT_SUCCESS);
}
