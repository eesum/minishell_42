/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_env_change.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohyeki <seohyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:34:51 by seohyeki          #+#    #+#             */
/*   Updated: 2024/03/19 14:11:23 by seohyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_value(char *new, char *name, size_t *j, t_list *env)
{
	size_t	i;
	char	*value;
	char	quote;

	i = 0;
	value = find_env(name, env);
	while (value[i])
	{
		if (ft_isquote(value[i]) || ft_ispipe(value[i])
			|| ft_isredirect(value[i]))
		{
			quote = '\"';
			if (ft_isquote(value[i]) == 2)
				quote = '\'';
			new[(*j)++] = quote;
			new[(*j)++] = value[i++];
			new[(*j)++] = quote;
		}
		else
			new[(*j)++] = value[i++];
	}
	free(value);
}

static void	no_change_vlaue(char *str, char *new, size_t *i, size_t *j)
{
	new[*j] = str[*i];
	(*j)++;
	(*i)++;
	while (str[*i] != '\'' && str[*i])
	{
		new[*j] = str[*i];
		(*j)++;
		(*i)++;
	}
	if (str[*i])
	{
		new[*j] = str[*i];
		(*j)++;
		(*i)++;
	}
}

void	change_env(char *str, t_list *env, char *new_str)
{
	size_t	i;
	size_t	j;
	char	*name;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (ft_isalpha(str[++i]) || str[i] == '_')
			{
				name = get_env_name(str + i);
				change_value(new_str, name, &j, env);
				i += ft_strlen(name);
				free(name);
			}
			else
				new_str[j++] = '$';
		}
		else if (str[i] == '\'')
			no_change_vlaue(str, new_str, &i, &j);
		else
			new_str[j++] = str[i++];
	}
}
