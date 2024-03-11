/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 13:38:45 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/11 13:04:20 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "./libft/libft.h"

int	count_heredoc(t_pipe *pipe)
{
	t_pipe	*pp_cur;
	t_token	*tk_cur;
	int		doc_cnt;

	pp_cur = pipe;
	doc_cnt = 0;
	while (pp_cur != NULL)
	{
		tk_cur = pp_cur->addr;
		while (tk_cur != NULL)
		{
			if (tk_cur->type == 3) // 숫자 확인. 매크로로 대체
				doc_cnt++;
			tk_cur = tk_cur->next;
		}
		pp_cur = pp_cur->next;
	}
	return (doc_cnt);
}

char	**parse_delimiter(t_pipe *pipe, int doc_cnt)
{
	t_pipe	*pp_cur;
	t_token	*tk_cur;
	char	**arr;
	int		i;

	arr = ft_malloc_err(sizeof(char *) * doc_cnt);
	pp_cur = pipe;
	i = 0;
	while (pp_cur != NULL)
	{
		tk_cur = pp_cur->addr;
		while (tk_cur != NULL)
		{
			if (tk_cur->type == 3) // 숫자 확인. 매크로로 대체
			{
				arr[i] = ft_strdup_err(tk_cur->str);
				i++;
			}
			tk_cur = tk_cur->next;
		}
		pp_cur = pp_cur->next;
	}
	return (doc_cnt);
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

void	here_document(t_pipe *pipe)
{
		//here doc 실행
		// heredoc 개수 확인
	// heredoc 개수 1개 이상이면, 그 동안 while 돌면서 순서대로 limiter에 지금 단어 집어넣고
	// 그 limiter와 같은거 나올때까지 memcmp?? 하면서 파일 열고 대기....
	// 파일 이름 겹치는 거 어떻게 해결하지???? random한 파일 제목 생성 같은거 해야하나,...?
	// 현재시간 ? 히어독
	int	doc_cnt;
	char	**arr;
	int	i;
	int	*fd;

	i = 0;
	doc_cnt = count_heredoc(pipe);
	if (doc_cnt == 0)
		return ;
	arr = parse_delimiter(pipe, doc_cnt);
	fd = ft_malloc_err(sizeof(int *) * doc_cnt + 1);
	fd[doc_cnt] = 0;


	char *tmpfile;
	char *buff;

	while (arr[i])
	{
		tmpfile = create_tmpname(i);
		fd[i] = open(tmpfile, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (fd[i] < 0)
			error_exit("file open failed", 0, 0, EXIT_FAILURE);
		while (1)
		{
			buff = readline("> ");
			if (buff != NULL)
			{
				if (ft_memcmp(arr[i], buff, ft_strlen(arr[i]) + 1) == 0)
					break ;
				write(fd[i], buff, ft_strlen(buff));
				write(fd[i], "\n", 1);
			}
		}
		i++;
	}
	
}

void	count_command(t_execdata *data)
{
	t_pipe	*cur;

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
	int	i;

	i = 0;
	here_document(data->pipe);
	count_command(data);
	while (data->cmd_cnt)

	// wait childe
	// heredoc 파일들 다 지우기??????
}


// t_env *parse_envp(char **envp)
// {
// 	t_env	*env;
// 	t_env	*cur;
// 	t_env	*new;
// 	int		i;

// 	i = 0;
// 	env = ft_malloc_err(sizeof(t_env));
// 	env->str = ft_strdup_err("?=");
// 	env->next = NULL;
// 	cur = env;
// 	while (envp[i])
// 	{
// 		new = ft_malloc_err(sizeof(t_env));
// 		new->str = ft_strdup_err(envp[i]);
// 		new->next = NULL;
// 		cur->next = new;
// 		cur = cur->next;
// 		i++;
// 	}
// 	return (env);
// }

t_list *envp_to_lst(char **envp)
{
	t_list	*env;
	t_list	*new;
	int		i;

	i = 0;
	env = ft_malloc_err(sizeof(t_list));
	env->content = ft_strdup_err("?=");
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
	t_list	*env;
	// t_execdata	data;

	env = envp_to_lst(envp);
	// data.env = env;
	// exec(&data);

	while (env != NULL)
	{
		printf("%s\n", env->content);
		env = env->next;
	}
	return (0);
}