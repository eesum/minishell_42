/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:22:02 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/23 17:25:20 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>

static void	input_to_heredoc(t_execdata *data, int i)
{
	char	*buff;

	while (1)
	{
		buff = readline("> \033[s");
		if (buff == NULL)
		{
			printf("\033[u");
			break ;
		}
		if (buff != NULL)
		{
			if (ft_memcmp(data->eof_arr[i], buff, \
				ft_strlen(data->eof_arr[i]) + 1) == 0)
			{
				free(buff);
				break ;
			}
			write(data->doc_fd[i], buff, ft_strlen(buff));
			write(data->doc_fd[i], "\n", 1);
		}
		free(buff);
	}
	close(data->doc_fd[i]);
}

static int	is_heredoc_signaled(t_list *env)
{
	char	*exit_code;

	exit_code = find_env("?", env);
	if (ft_memcmp(exit_code, "100", 4) == 0)
	{
		free(exit_code);
		return (1);
	}
	free(exit_code);
	return (0);
}

int	here_document(t_execdata *data)
{
	int		i;

	i = 0;
	before_heredoc(data);
	data->pid[0] = fork();
	if (data->pid[0] < 0)
		error_exit("fork failed", 0, 0, EXIT_FAILURE);
	if (data->pid[0] == 0)
	{
		signal(SIGINT, &heredoc_sig);
		i = 0;
		while (i < data->doc_cnt)
		{
			data->doc_fd[i] = open(data->file_arr[i], O_RDWR | O_CREAT, 0644);
			if (data->doc_fd[i] < 0)
				error_exit("file open failed", 0, 0, EXIT_FAILURE);
			input_to_heredoc(data, i++);
		}
		exit(EXIT_SUCCESS);
	}
	signal(SIGINT, SIG_IGN);
	wait_and_update_exit_code(data->pid, data->env);
	if (is_heredoc_signaled(data->env) == 1)
		return (-1);
	return (0);
}
