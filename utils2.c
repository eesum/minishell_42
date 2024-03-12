/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 21:02:59 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/12 20:06:37 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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