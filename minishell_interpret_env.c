/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_interpret_env.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohyeki <seohyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:34:51 by seohyeki          #+#    #+#             */
/*   Updated: 2024/03/13 20:54:12 by seohyeki         ###   ########.fr       */
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
	while(ft_isalnum(str[i]) || str[i] == '_')
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

static void	no_interpret_env(char *str, size_t *i)
{
	(*i)++;
	while (str[*i] != '\'' && str[*i])
		(*i)++;
	if (str[*i])
		(*i)++;
}

static void	count_total_len(char *str, t_list *envlist, size_t *len)
{
	size_t	i;
	char	*name;
	char	*value;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			if (ft_isalpha(str[i]) || str[i] == '_')
			{
				name = get_env_name(str + i);
				value = find_env(name, envlist);
				(*len) = (*len) - (ft_strlen(name) + 1) + ft_strlen(value);
				free(name);
				free(value);
			}
		}
		else if (str[i] == '\'')
			no_interpret_env(str + i, &i);
		else
			i++;
	}
}

char *interpret_env(char *str, t_list *envlist)
{
	size_t	total_len;
	char	*new;
	
	if (str == NULL)
		return (NULL);
	total_len = ft_strlen(str);
	count_total_len(str, envlist, &total_len);
	printf("total_len: %zu\n", total_len);
	new = (char *)ft_malloc_err(sizeof(char) * (total_len + 1));
	new[total_len] = '\0';
	change_env(str, envlist, new);
	return (new);
}
