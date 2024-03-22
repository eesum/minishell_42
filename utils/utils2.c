/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohyeki <seohyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 21:02:59 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/22 15:36:45 by seohyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_err(char const *s1, char const *s2)
{
	size_t	strlen;
	char	*arr;

	strlen = ft_strlen(s1) + ft_strlen(s2);
	arr = (char *)malloc(sizeof(char) * (strlen + 1));
	if (arr == NULL)
		error_exit("malloc failed", 0, 0, EXIT_FAILURE);
	arr[0] = '\0';
	ft_strcat(arr, s1);
	ft_strcat(arr, s2);
	return (arr);
}

char	*ft_substr_err(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	i;
	size_t			s_len;

	i = 0;
	s_len = ft_strlen(s);
	if (s_len <= start)
		len = 0;
	else if (s_len < start + len)
		len = s_len - start;
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (sub == NULL)
		error_exit("malloc failed", 0, 0, EXIT_FAILURE);
	while (i < len && s[start + i])
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

char	*ft_strjoin_sep(char const *s1, char const *s2, char const *sep)
{
	size_t	strlen;
	char	*arr;

	strlen = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	strlen = ft_strlen(s1) + ft_strlen(s2) + 1;
	arr = (char *)malloc(sizeof(char) * (strlen + 1));
	if (arr == NULL)
		error_exit("malloc failed.", 0, 0, EXIT_FAILURE);
	arr[0] = '\0';
	ft_strcat(arr, s1);
	ft_strcat(arr, sep);
	ft_strcat(arr, s2);
	return (arr);
}

void	wait_and_update_exit_code(pid_t *pid, t_list *env)
{
	int		i;
	int		status;
	pid_t	wait_pid;
	char	*exit_code_char;

	i = 0;
	while (pid && pid[i])
	{
		wait_pid = waitpid(pid[i], &status, 0);
		if (wait_pid < 0)
			error_exit("wait error", 0, 0, EXIT_FAILURE);
		else if (WIFEXITED(status))
			exit_code_char = ft_itoa_err(WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
		{
			printf("\n");
			exit_code_char = ft_itoa_err(128 + WTERMSIG(status));
		}
		update_env("?", exit_code_char, env);
		free(exit_code_char);
		i++;
	}
	set_terminal_print_off();
	signal(SIGINT, &parent_sig);
}

t_list	*ft_findlst_by_index(t_list *lst, int i)
{
	t_list	*cur;
	int		index;

	index = 0;
	cur = lst;
	while (index < i && cur->next != NULL)
	{
		index ++;
		cur = cur->next;
	}
	return (cur);
}