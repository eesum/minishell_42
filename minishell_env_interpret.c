/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_env_interpret.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohyeki <seohyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:34:51 by seohyeki          #+#    #+#             */
/*   Updated: 2024/03/16 16:12:22 by seohyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_name(char *str)
{
	size_t	i;
	size_t	size;
	char	*name;

	i = 0;
	size = 0;
	while (ft_isalnum(str[i]) || str[i] == '_')
	{
		i++;
		size++;
	}
	name = (char *)ft_malloc_err(sizeof(char) * (size + 1));
	name[size] = '\0';
	i = 0;
	while (i < size)
	{
		name[i] = str[i];
		i++;
	}
	return (name);
}

static void	interpret_env(char *str, t_list *env, size_t *len, size_t *index)
{
	char	*name;
	char	*value;
	size_t	meta;
	size_t	i;

	name = get_env_name(str + (*index));
	value = find_env(name, env);
	meta = 0;
	i = 0;
	while (value[i])
	{
		if (ft_isquote(value[i]) || ft_ispipe(value[i])
			|| ft_isredirect(value[i]))
			meta++;
		i++;
	}
	(*len) = (*len) - (ft_strlen(name) + 1) + ft_strlen(value) + (meta * 2);
	free(name);
	free(value);
}

static void	no_interpret_env(char *str, size_t *i)
{
	(*i)++;
	while (str[*i] != '\'' && str[*i])
		(*i)++;
	if (str[*i])
		(*i)++;
}

static void	count_total_len(char *str, t_list *env, size_t *len)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			if (ft_isalpha(str[i]) || str[i] == '_')
				interpret_env(str, env, len, &i);
		}
		else if (str[i] == '\'')
			no_interpret_env(str + i, &i);
		else
			i++;
	}
}

char	*parsing_env(char *str, t_list *env)
{
	size_t	total_len;
	char	*new;

	if (str == NULL)
		return (NULL);
	total_len = ft_strlen(str);
	count_total_len(str, env, &total_len);
	new = (char *)ft_malloc_err(sizeof(char) * (total_len + 1));
	new[total_len] = '\0';
	change_env(str, env, new);
	return (new);
}
