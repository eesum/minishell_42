/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 13:38:45 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/11 18:43:56 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_childs(t_execdata *data)
{
	int		i;
	pid_t	wait_pid;

	i = 0;
	while (i < data->cmd_cnt)
	{
		wait_pid = wait(&data->status);// 여기 확인 필요
		if (wait_pid < 0 || WIFEXITED(data->status) == 0 || \
			WEXITSTATUS(data->status) != 0)
			exit(EXIT_FAILURE);
		i++;
	}
}

void	count_command(t_execdata *data)
{
	t_list	*cur;

	data->cmd_cnt = 0;
	cur = data->pipe;
	while (cur != NULL)
	{
		data->cmd_cnt++;
		cur = cur->next;
	}
}

void	exec(t_execdata *data)
{
	here_document(data);
	count_command(data);
	data->index = 0;
	while (data->index < data->cmd_cnt)
	{
		if (data->index < data->cmd_cnt - 1)
			if (pipe(data->fd[data->index % 2]) < 0)
				error_exit("pipe failed.", 0, 0, EXIT_FAILURE);
		data->pid = fork();
		if (data->pid < 0)
			error_exit("fork failed.", 0, 0, EXIT_FAILURE);
		else if (data->pid == 0)
			exec_in_child(data);
		else
		{
			if (data->index < data->cmd_cnt - 1)
				close(data->fd[data->index % 2][1]);
			if (data->index > 0)
				close(data->fd[(data->index + 1) % 2][0]);
		}
		data->index++;
	}
	wait_childs(data);
	// heredoc 파일들 다 지우기??????
}


t_list *envp_to_lst(char **envp)
{
	t_list	*env;
	t_list	*new;
	int		i;

	i = 0;
	env = ft_malloc_err(sizeof(t_list));
	env->content = ft_strdup_err("?=0");
	env->next = NULL;
	while (envp[i])
	{
		new = ft_malloc_err(sizeof(t_list));
		new->content = ft_strdup_err(envp[i]);
		ft_lstadd_back(&env, new);
		i++;
	}
	return (env);
}

int	main(int argc, char **argv, char **envp)
{
	t_execdata	data;
	
	data.env = envp_to_lst(envp);
	exec(&data);

	while (data.env != NULL)
	{
		printf("%s\n", data.env->content);
		data.env = data.env->next;
	}
	return (0);
}