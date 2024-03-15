/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 13:38:45 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/15 14:56:52 by sumilee          ###   ########.fr       */
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
	if (data->pipe_cnt == 1 && is_builtin(cmd) != 0)
		return (1);
	return (0);
}

char	**cmd_to_arr(t_list *pipe)
{
	t_list *cur;
	int		cnt;
	char	**cmd;

	cnt = 0;
	cur = pipe;
	while (cur != NULL)
	{
		if (((t_token *)cur->content)->type == 0)
			cnt++;
		cur = cur->next;
	}
	if (cnt == 0)
		return (NULL);
	cmd = ft_malloc_err(sizeof(char *) * (cnt + 1));
	cmd[cnt] = NULL;
	cnt = -1;
	cur = pipe;
	while (cur != NULL)
	{
		if (((t_token *)cur->content)->type == 0)
			cmd[++cnt] = ft_strdup_err(((t_token *)cur->content)->str);
		cur = cur->next;
	}
	return (cmd);
}

int	exec_cmd(char **cmd, t_list *env)
{
	if (cmd == NULL)
		return (0) ;
	else if (ft_memcmp(cmd[0], "echo", 5) == 0)
		return (exec_echo(cmd));
	else if (ft_memcmp(cmd[0], "cd", 3) == 0)
		return (exec_cd(cmd, env));
	else if (ft_memcmp(cmd[0], "pwd", 4) == 0)
		return (exec_pwd(cmd));
	else if (ft_memcmp(cmd[0], "export", 7) == 0)
		return (exec_export(cmd, env));
	else if (ft_memcmp(cmd[0], "unset", 6) == 0)
		return (exec_unset(cmd, env));
	else if (ft_memcmp(cmd[0], "env", 4) == 0)
		return (exec_env(cmd, env));
	else if (ft_memcmp(cmd[0], "exit", 5) == 0)
		exec_exit(cmd);
	else
		exec_general_cmd(cmd, env);
	return (0);
}

int	only_builtin(t_execdata *data)
{
	int	input;
	int	output;
	char	**cmd;
	char	*exit_code;

	if (check_file_open(data->pipe->content) < 0)
		return (-1);
	input = open_last_input(data->pipe, data->file_arr);
	output = open_last_output(data->pipe);
	dup_fds(data, input, output);
	cmd = cmd_to_arr(data->pipe->content);
	if (exec_cmd(cmd, data->env) < 0)
		return (-1);
	dup2(data->tmp_fd[0], 0);
	dup2(data->tmp_fd[1], 1);
	close(data->tmp_fd[0]);
	close(data->tmp_fd[1]);
	return (0);
}

void	exec_in_child(t_execdata *data)
{
	if (check_file_open(data->pipe->content) < 0)
		exit(EXIT_FAILURE);
	
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
			exec_in_child(data);
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
}

void	exec(t_execdata *data)
{
	init_token_flags(data);
	here_document(data);
	if (count_pipe(data) == 0 || data->pipe_cnt == 1)
	{
		if (data->pipe_cnt == 1)
		{
			if (only_builtin(data) < 0)
				update_env("?", "1", data->env);
			else
			 	update_env("?", "0", data->env);
		}
		return ;
	}
	exec_multiple_pipe(data);
	// heredoc 파일들 다 지우기??????
}


t_list *envp_to_lst(char **envp)
{
	t_list	*env;
	t_list	*new;
	int		i;

	i = 0;
	env = ft_lstnew(ft_strdup_err("?=0"));
	if (env == NULL)
		error_exit("malloc failed", 0, 0, EXIT_FAILURE);
	while (envp && envp[i])
	{
		new = ft_lstnew(ft_strdup_err(envp[i]));
		if (env == NULL)
			error_exit("malloc failed", 0, 0, EXIT_FAILURE);
		ft_lstadd_back(&env, new);
		i++;
	}
	return (env);
}

void	debug_print(char *file, int line, const char *func)
{
	printf("=======FILE: %s / LINE: %d / FUNC: %s=======\n", file, line, func);
}

int	main(int argc, char **argv, char **envp)
{
	t_execdata	data;
	t_list		*new;
	t_list		*first_token;
	char		*buff;
	
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
	
	t_token *t5 = ft_malloc_err(sizeof(t_token));
	new = ft_lstnew(t5);
	ft_lstadd_back(&first_token, new);
	
	// t_token *t6 = ft_malloc_err(sizeof(t_token));
	// new = ft_lstnew(t6);
	// ft_lstadd_back(&first_token, new);
	
	// t_token *t7 = ft_malloc_err(sizeof(t_token));
	// new = ft_lstnew(t7);
	// ft_lstadd_back(&first_token, new);
	
	// t_token *t8 = ft_malloc_err(sizeof(t_token));
	// new = ft_lstnew(t8);
	// ft_lstadd_back(&first_token, new);

	t1->str = "a";
	t1->type=TYPE_HEREDOC;

	t2->str = "eof";
	t2->type=TYPE_HEREDOC;

	t3->str = "export";
	t3->type=TYPE_DEFAULT;
	t4->str = "out_t";
	t4->type=TYPE_OUTPUT_T;
	t5->str = "out_a";
	t5->type=TYPE_OUTPUT_A;
	// t6->str = "eof";
	// t6->type=TYPE_HEREDOC;
	// t7->str = "eof";
	// t7->type=TYPE_HEREDOC;
	// t8->str = "eof";
	// t8->type=TYPE_HEREDOC;

	while (1)
	{
		buff = readline("minishell$ ");
		exec(&data);
		
		free (buff);
		buff = NULL;
	}

	// while (data.env != NULL)
	// {
	// 	printf("%s\n", data.env->content);
	// 	data.env = data.env->next;
	// }
	return (0);
}