/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohyeki <seohyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:22:02 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/28 14:55:38 by seohyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "util.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <sys/fcntl.h>

static void	input_to_heredoc(t_execdata *data, int i)
{
	char	*buff;
	int		fd;

	fd = open(data->file_arr[i], O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
		error_exit("file open failed", 0, 0, EXIT_FAILURE);
	while (1)
	{
		buff = readline("> \001\033[s\002");
		if (buff == NULL)
		{
			printf("\033[u\033[1B\033[1A");
			break ;
		}
		if (ft_memcmp(data->eof_arr[i], buff, \
			ft_strlen(data->eof_arr[i]) + 1) == 0)
		{
			free(buff);
			break ;
		}
		write(fd, buff, ft_strlen(buff));
		write(fd, "\n", 1);
		free(buff);
	}
	close(fd);
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
	int		exit_num;
	char	*exit_code;

	i = 0;
	before_heredoc(data);
	data->pid[0] = fork();
	if (data->pid[0] < 0)
		error_exit("fork failed", 0, 0, EXIT_FAILURE);
	if (data->pid[0] == 0)
	{
		signal(SIGINT, &heredoc_sig);
		while (i < data->doc_cnt)
			input_to_heredoc(data, i++);
		exit(EXIT_SUCCESS);
	}
	signal(SIGINT, SIG_IGN);
	exit_num = wait_and_update_exit_code(data->pid);
	exit_code = ft_itoa_err(exit_num);
	update_env("?", exit_code, data->env);
	return (is_heredoc_signaled(data->env));
}
