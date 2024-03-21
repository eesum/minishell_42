/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:22:02 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/21 20:36:11 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**parse_delimiter(t_list *pipe, int doc_cnt)
{
	t_list	*pp_cur;
	t_list	*tk_cur;
	char	**arr;
	int		i;

	arr = ft_malloc_err(sizeof(char *) * doc_cnt + 1);
	arr[doc_cnt] = 0;
	pp_cur = pipe;
	i = 0;
	while (pp_cur != NULL)
	{
		tk_cur = pp_cur->content;
		while (tk_cur != NULL)
		{
			if (((t_token *)tk_cur->content)->type == TYPE_HEREDOC)
			{
				arr[i] = ft_strdup_err(((t_token *)tk_cur->content)->str);
				i++;
			}
			tk_cur = tk_cur->next;
		}
		pp_cur = pp_cur->next;
	}
	return (arr);
}

char	*create_tmpname(int i)
{
	char	*name;
	char	*tmp;
	char	*num;

	num = ft_itoa_err(i);
	name = ft_strjoin_err("./.", num);
	while (access(name, F_OK) == 0)
	{
		tmp = name;
		name = ft_strjoin_err(tmp, num);
		free(tmp);
	}
	free(num);
	return (name);
}

void	before_heredoc(t_execdata *data)
{
	int	i;

	i = 0;
	if (data->doc_cnt == 0)
	{
		data->eof_arr = NULL;
		data->doc_fd = NULL;
		data->file_arr = NULL;
		return ;
	}
	data->eof_arr = parse_delimiter(data->pipe, data->doc_cnt);
	data->doc_fd = ft_malloc_err(sizeof(int *) * data->doc_cnt + 1);
	data->doc_fd[data->doc_cnt] = 0;
	data->file_arr = ft_malloc_err(sizeof(char *) * data->doc_cnt + 1);
	data->file_arr[data->doc_cnt] = 0;
	while (i < data->doc_cnt)
	{
		data->file_arr[i] = create_tmpname(i);
		i++;
	}
}

void	input_to_heredoc(t_execdata *data, char *file_name, int i)
{
	char	*buff;

	data->doc_fd[i] = open(file_name, O_RDWR | O_CREAT, 0644);
	if (data->doc_fd[i] < 0)
		error_exit("file open failed", 0, 0, EXIT_FAILURE);
	while (1)
	{
		buff = readline("> ");
		if (buff == NULL)
			break ;
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
		buff = NULL;
	}
	close(data->doc_fd[i]);
}

int	is_heredoc_signaled(t_list *env)
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
	pid_t	pid;

	i = 0;
	before_heredoc(data);
	pid = fork();
	if (pid < 0)
		error_exit("fork failed", 0, 0, EXIT_FAILURE);
	if (pid == 0)
	{
		signal(SIGINT, &heredoc_sig);
		i = 0;
		while (i < data->doc_cnt)
		{
			input_to_heredoc(data, data->file_arr[i], i);
			i++;
		}
		exit(EXIT_SUCCESS);
	}
	signal(SIGINT, SIG_IGN);
	wait_and_update_exit_code(1, data->env);
	if(is_heredoc_signaled(data->env) == 1)
		return (-1);
	return (0);
}
