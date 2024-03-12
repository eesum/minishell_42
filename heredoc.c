/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:22:02 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/12 18:24:17 by sumilee          ###   ########.fr       */
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
			if (((t_token *)tk_cur->content)->type == 3) // 숫자 확인. 매크로로 대체
				doc_cnt++;
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

	arr = ft_malloc_err(sizeof(char *) * doc_cnt);
	pp_cur = pipe;
	i = 0;
	while (pp_cur != NULL)
	{
		tk_cur = pp_cur->content;
		while (tk_cur != NULL)
		{
			if (((t_token *)tk_cur->content)->type == 3) // 숫자 확인. 매크로로 대체
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

	num = ft_itoa(i);
	path = ft_strjoin("./.", num);
	while (access(path, F_OK) == 0)
	{
		tmp = path;
		path = ft_strjoin(tmp, num);
		free(tmp);
	}
	free(num);
	return (path);
}

void	here_document(t_execdata *data)  // 시그널 등 추후 고려 필요
{
	int	i;

	i = 0;
	data->doc_cnt = count_heredoc(data->pipe);
	if (data->doc_cnt == 0)
		return ;
	data->doc_arr = parse_delimiter(data->pipe, data->doc_cnt);
	data->doc_fd = ft_malloc_err(sizeof(int *) * data->doc_cnt + 1);
	data->doc_fd[data->doc_cnt] = 0;


	char *tmpfile;
	char *buff;

	while (data->doc_arr[i])
	{
		tmpfile = create_tmpname(i);
		data->doc_fd[i] = open(tmpfile, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (data->doc_fd[i] < 0)
			error_exit("file open failed", 0, 0, EXIT_FAILURE);
		while (1)
		{
			buff = readline("> ");
			if (buff != NULL)
			{
				if (ft_memcmp(data->doc_arr[i], buff, ft_strlen(data->doc_arr[i]) + 1) == 0)
					break ;
				write(data->doc_fd[i], buff, ft_strlen(buff));
				write(data->doc_fd[i], "\n", 1);
			}
			free(buff);
		}
		i++;
	}
	
}
