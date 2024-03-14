/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:22:02 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/14 19:41:13 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_heredoc(t_list *pipe)
{
	t_list	*pp_cur;
	t_list	*tk_cur;
	int		doc_cnt;

	pp_cur = pipe;
	doc_cnt = 0;
	while (pp_cur != NULL)
	{
		tk_cur = pp_cur->content;
		while (tk_cur != NULL)
		{
			((t_token *)tk_cur->content)->hd_index = -1;
			if (((t_token *)tk_cur->content)->type == TYPE_HEREDOC)
			{
				doc_cnt++;
				((t_token *)tk_cur->content)->hd_index = doc_cnt;
			}
			tk_cur = tk_cur->next;
		}
		pp_cur = pp_cur->next;
	}
	return (doc_cnt);
}

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
	char	*path;
	char	*name;
	char	*tmp;
	char	*num;

	num = ft_itoa_err(i);
	path = ft_strjoin_err("./.", num);
	while (access(path, F_OK) == 0)
	{
		tmp = path;
		path = ft_strjoin_err(tmp, num);
		free(tmp);
	}
	free(num);
	return (path);
}

void	before_heredoc(t_execdata *data)
{
	int	i;

	i = 0;
	data->doc_cnt = count_heredoc(data->pipe);
	if (data->doc_cnt == 0)
		return ;
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
			if (data->eof_arr[i][0] == '\0')
				break ;
		if (buff != NULL)
		{
			if (ft_memcmp(data->eof_arr[i], buff, ft_strlen(data->eof_arr[i]) + 1) == 0)
				break ;
			write(data->doc_fd[i], buff, ft_strlen(buff));
			write(data->doc_fd[i], "\n", 1);
		}
		free(buff);
		buff = NULL;
	}
	close(data->doc_fd[i]);
	//시그널 받는거...
}

void	here_document(t_execdata *data)  // 시그널 등 추후 고려 필요
{
	int	i;
	pid_t	pid;

	i = 0;
	before_heredoc(data);
	// pid = ft_malloc_err(sizeof(pid_t) * (data->doc_cnt + 1));
	// pid[data->doc_cnt] = 0;
	
	pid = fork();
	if (pid < 0)
		error_exit("fork failed", 0, 0, EXIT_FAILURE);
	if (pid == 0)
	{
		i = 0;
		while (i < data->doc_cnt)
		{
			input_to_heredoc(data, data->file_arr[i], i);
			i++;
		}
		exit(EXIT_SUCCESS);
	}
	wait_and_update_exit_code(1, data->env);
}
