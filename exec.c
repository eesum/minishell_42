/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 13:38:45 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/18 13:52:05 by sumilee          ###   ########.fr       */
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
	int	input;
	int	output;
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
		return (-1);
	}
	restore_fds(data, input, output);
	return (0);
}

void	delete_tmpfile(t_execdata *data)
{
	int	i;

	i = 0;
	while (data->file_arr[i])
	{
		if (unlink(data->file_arr[i]) < 0)
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
			exec_in_child(data, data->index);
		}
		else
		{
			if (data->index < data->pipe_cnt - 1)
				close(data->fd[data->index % 2][1]);
			if (data->index > 0)
				close(data->fd[(data->index + 1) % 2][0]);
		}
		data->index++;
	}
	wait_and_update_exit_code(data->pipe_cnt, data->env);
	delete_tmpfile(data);
}

void	exec(t_execdata *data)
{
	init_token_flags(data);
	here_document(data);
	if (count_pipe(data) == 1)
	{
		if (only_builtin(data) < 0)
			update_env("?", "1", data->env);
		else
			update_env("?", "0", data->env);
		delete_tmpfile(data);
		return ;
	}
	exec_multiple_pipe(data);
	free_arr(data->eof_arr);
	free_arr(data->file_arr);
	ft_lstclear(&data->env, free);
	free(data->doc_fd);
}


void check()
{
	system("leaks --list a.out");
}

int	main(int argc, char **argv, char **envp)
{
	t_execdata	data;
	t_list		*new;
	t_list		*first_token;
	char		*buff;
	
	atexit(check);
	data.env = envp_to_lst(envp);
	data.pipe = ft_malloc_err(sizeof(t_list));

	t_token *t1 = ft_malloc_err(sizeof(t_token));
	first_token = ft_lstnew(t1);
	data.pipe->content = first_token;
	data.pipe->next = NULL;
	
	t_token *t2 = ft_malloc_err(sizeof(t_token));
	new = ft_lstnew(t2);
	ft_lstadd_back(&first_token, new);
	
	t_token *t3 = ft_malloc_err(sizeof(t_token));
	new = ft_lstnew(t3);
	ft_lstadd_back(&first_token, new);
	
	t_token *t4 = ft_malloc_err(sizeof(t_token));
	new = ft_lstnew(t4);
	ft_lstadd_back(&first_token, new);
	
	// t_token *t5 = ft_malloc_err(sizeof(t_token));
	// new = ft_lstnew(t5);
	// ft_lstadd_back(&first_token, new);

	t1->str = "a";
	t1->type=TYPE_INPUT;

	t2->str = "eof";
	t2->type=TYPE_HEREDOC;

	t3->str = "ls";
	t3->type=TYPE_DEFAULT;

	t4->str = "-al";
	t4->type=TYPE_DEFAULT;
	// t5->str = "out_a";
	// t5->type=TYPE_OUTPUT_A;


	t_list		*new_pipe;
	t_list		*sec_first_token;
	

	new_pipe = ft_malloc_err(sizeof(t_list));
	t_token *t21 = ft_malloc_err(sizeof(t_token));
	sec_first_token = ft_lstnew(t21);
	new_pipe->content = sec_first_token;
	new_pipe->next = NULL;
	ft_lstadd_back(&data.pipe, new_pipe);

	t_token *t22 = ft_malloc_err(sizeof(t_token));
	new = ft_lstnew(t22);
	ft_lstadd_back(&sec_first_token, new);
	
	// t_token *t23 = ft_malloc_err(sizeof(t_token));
	// new = ft_lstnew(t23);
	// ft_lstadd_back(&sec_first_token, new);
	
	t_token *t24 = ft_malloc_err(sizeof(t_token));
	// printf("t24: %p\n", t24);
	new = ft_lstnew(t24);
	// printf("new: %p\n", new);
	ft_lstadd_back(&sec_first_token, new);
	
	t_token *t25 = ft_malloc_err(sizeof(t_token));
	// printf("t25: %p\n", t25);
	new = ft_lstnew(t25);
	// printf("new: %p\n", new);
	ft_lstadd_back(&sec_first_token, new);

	t21->str = "grep";
	t21->type=TYPE_DEFAULT;

	t22->str = "minishell";
	t22->type=TYPE_DEFAULT;

	// t23->str = "grep";
	// t23->type=TYPE_DEFAULT;
	t24->str = "out_t";
	t24->type=TYPE_OUTPUT_T;
	t25->str = "out_a";
	t25->type=TYPE_OUTPUT_A;

	while (1)
	{
		buff = readline("minishell$ ");
		free (buff);
		buff = NULL;
		exec(&data);
	}

	// while (data.env != NULL)
	// {
	// 	printf("%s\n", data.env->content);
	// 	data.env = data.env->next;
	// }

	exit(EXIT_SUCCESS);
	return (0);
}