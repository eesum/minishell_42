/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:21:29 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/18 13:23:40 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list *envp_to_lst(char **envp)
{
	t_list	*env;
	t_list	*new;
	int		i;

	i = 0;
	env = ft_lstnew(ft_strdup_err("?=0"));
	if (env == NULL)
		error_exit("malloc failed", 0, 0, EXIT_FAILURE);
	while (envp && envp[i])
	{
		new = ft_lstnew(ft_strdup_err(envp[i]));
		if (env == NULL)
			error_exit("malloc failed", 0, 0, EXIT_FAILURE);
		ft_lstadd_back(&env, new);
		i++;
	}
	return (env);
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
