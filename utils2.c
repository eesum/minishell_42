/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohyeki <seohyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 21:02:59 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/14 14:33:11 by seohyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*find_env(char *name, t_list *env)
{
	char	*value;
	t_list	*cur;
	size_t	name_len;

	value = NULL;
	cur = env;
	if (name == NULL)
		return (NULL);
	name_len = ft_strlen(name);
	while (cur != NULL)
	{
		if (ft_strncmp((char *)cur->content, name, name_len) == 0 \
			&& ((char *)cur->content)[name_len] == '=' \
			&& ((char *)cur->content)[name_len] != '\0')
		{
			value = ft_strdup_err(&((char *)cur->content)[name_len + 1]);
			return (value);
		}
		cur = cur->next;
	}
	if (value == NULL)
		value = ft_malloc_err(1);
	value[0] = '\0';
	return (value);
}

void	update_env(char *name, char *value, t_list *env)
{
	t_list	*cur;
	size_t	name_len;
	char	*env_content;
	t_list	*new;

	cur = env;
	if (name == NULL)
		return ;
	name_len = ft_strlen(name);
	while (cur != NULL)
	{
		if (ft_memcmp((char *)cur->content, name, name_len) == 0 \
			&& ((char *)cur->content)[name_len] == '=' \
			&& ((char *)cur->content)[name_len] != '\0')
		{
			free(cur->content);
			cur->content= ft_strjoin_sep(name, value, "=");
			return ;
		}
		cur = cur->next;
	}
	new = ft_lstnew(ft_strjoin_sep(name, value, "="));
	if (new == NULL)
		error_exit("malloc failed", 0, 0, EXIT_FAILURE);
	ft_lstadd_back(&env, new);
}

void	check_cmd_option(char **cmd)
{
	char	tmp[3];

	if (cmd[1] && cmd[1][0] == '-' && cmd[1][1] != '\0')
	{
		tmp[0] = '-';
		tmp[1] = cmd[1][1];
		tmp[2] = '\0';
		error_exit("invalid option", cmd[0], tmp, 2);
	}
}

int	check_valid_name(char *arg, char sep)
{
	int	i;

	if (arg && arg[0] != 95 && \
		(arg[0] < 65 || (arg[0] > 90 && arg[0] < 97) || arg[0] > 122))
		return (-1);
	i = 1;
	while (arg && arg[i] && arg[i] != sep)
	{
		if (arg[i] != 95 && \
			(arg[i] < 48 || (arg[i] > 57 && arg[i] < 65) || \
			(arg[i] > 90 && arg[i] < 97) || arg[i] > 122))
			return (-1);
		i++;
	}
	return (i);
}

void	wait_and_update_exit_code(int doc_cnt, t_list *env)
{
	int		i;
	int		status;
	pid_t	wait_pid;
	char	*exit_code_char;
	int		sig_code;

	i = 0;
	while(i < doc_cnt)
	{
		wait_pid = wait(&status);
		if (wait_pid < 0)
			error_exit("wait error", 0, 0, EXIT_FAILURE);
		else if (WIFEXITED(status))
			exit_code_char = ft_itoa_err(WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
		{
			sig_code = 128 + WTERMSIG(status);
			exit_code_char = ft_itoa_err(sig_code);
		}
		update_env("?", exit_code_char, env);
		i++;
	}
}

int	is_builtin(char *cmd)
{
	if (cmd == NULL)
		return (0);
	if (!ft_memcmp("echo", cmd, 5))
		return (1);
	if (!ft_memcmp("cd", cmd, 3))
		return (2);
	if (!ft_memcmp("pwd", cmd, 4))
		return (3);
	if (!ft_memcmp("export", cmd, 7))
		return (4);
	if (!ft_memcmp("unset", cmd, 6))
		return (5);
	if (!ft_memcmp("exit", cmd, 5))
		return (6);
	return (0);
}
