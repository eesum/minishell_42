/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 13:38:45 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/21 20:56:11 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipe(t_execdata *data)
{
	t_list	*cur;
	t_list	*cur_token;
	char	*cmd;

	data->pipe_cnt = 0;
	cur = data->pipe;
	cmd = NULL;
	while (cur != NULL)
	{
		data->pipe_cnt++;
		cur_token = cur->content;
		while (cur_token != NULL)
		{
			if (((t_token *)cur_token->content)->type == TYPE_DEFAULT)
			{
				cmd = ((t_token *)cur_token->content)->str;
				break ;
			}
			cur_token = cur_token->next;
		}
		cur = cur->next;
	}
	if (data->pipe_cnt == 1 && is_builtin(cmd) > 0 && is_builtin(cmd) < 8)
		return (1);
	return (0);
}

int	only_builtin(t_execdata *data)
{
	int		input;
	int		output;
	char	**cmd;

	cmd = cmd_to_arr(data->pipe->content);
	if (check_file_open(data->pipe->content) < 0 || cmd == NULL)
		return (-1);
	input = open_last_input(data->pipe, data->file_arr);
	output = open_last_output(data->pipe);
	dup_fds(data, input, output);
	if (exec_cmd(cmd, data->env) < 0)
	{
		restore_fds(data, input, output);
		free_arr(cmd);
		return (-1);
	}
	restore_fds(data, input, output);
	free_arr(cmd);
	return (0);
}

void	delete_tmpfile(t_execdata *data)
{
	int	i;

	i = 0;
	while (data->file_arr && data->file_arr[i])
	{
		if (access(data->file_arr[i], F_OK) == 0 && unlink(data->file_arr[i]) < 0)
			error_msg_only("file unlink failed", data->file_arr[i], 0);
		i++;
	}
}

void	exec_multiple_pipe(t_execdata *data)
{
	data->index = 0;
	while (data->index < data->pipe_cnt)
	{
		if (data->index < data->pipe_cnt - 1)
			if (pipe(data->fd[data->index % 2]) < 0)
				error_exit("pipe failed.", 0, 0, EXIT_FAILURE);
		data->pid = fork();
		if (data->pid < 0)
			error_exit("fork failed.", 0, 0, EXIT_FAILURE);
		else if (data->pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			set_terminal_print_on();
			exec_in_child(data, data->index);
		}
		signal(SIGINT, SIG_IGN);
		if (data->index < data->pipe_cnt - 1)
			close(data->fd[data->index % 2][1]);
		if (data->index > 0)
			close(data->fd[(data->index + 1) % 2][0]);
		data->index++;
	}
	wait_and_update_exit_code(data->pipe_cnt, data->env);
}

void	end_exec(t_execdata *data)
{
	delete_tmpfile(data);
	free_arr(data->eof_arr);
	free_arr(data->file_arr);
	if (data->doc_fd != NULL)
		free(data->doc_fd);
	ft_lstclear(&data->pipe, free_tokens_in_pipe);
}

void	exec(t_execdata *data)
{
	init_token_flags(data);
	if (here_document(data) < 0)
	{
		end_exec(data);
		update_env("?", "1", data->env);
		return ;
	}
	if (count_pipe(data) == 1)
	{
		if (only_builtin(data) < 0)
			update_env("?", "1", data->env);
		else
			update_env("?", "0", data->env);
		end_exec(data);
		return ;
	}
	exec_multiple_pipe(data);
	end_exec(data);
}
