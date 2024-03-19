/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_env_change.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohyeki <seohyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:34:51 by seohyeki          #+#    #+#             */
/*   Updated: 2024/03/19 17:48:21 by seohyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_value(t_parsedata *data, size_t *i, size_t *j, t_list *env)
{
	size_t	k;
	char	*name;
	char	*src;
	char	quote;

	k = 0;
	name = get_env_name(data->str + *i);
	src = find_env(name, env);
	while (src[k])
	{
		if (ft_isquote(src[k]) || ft_ispipe(src[k]) || ft_isredirect(src[k]))
		{
			quote = '\"';
			if (ft_isquote(src[k]) == 2)
				quote = '\'';
			data->env_str[(*j)++] = quote;
			data->env_str[(*j)++] = src[k++];
			data->env_str[(*j)++] = quote;
		}
		else
			data->env_str[(*j)++] = src[k++];
	}
	(*i) += ft_strlen(name);
	free(name);
	free(src);
}

void	change_env_quote(t_parsedata *data, size_t *i, size_t *j, t_list *env)
{
	data->env_str[(*j)++] = data->str[(*i)++];
	while (ft_isquote(data->str[*i]) != 2 && data->str[*i])
	{
		if (data->str[*i] == '$')
		{
			data->env_str[(*j)++] = '\"';
			if (ft_isalpha(data->str[++(*i)]) || data->str[*i] == '_'
				|| data->str[*i] == '?')
			{
				change_value(data, i, j, env);
				data->env_str[(*j)++] = '\"';
			}
			else
				data->env_str[(*j)++] = '$';
		}
		else
			data->env_str[(*j)++] = data->str[(*i)++];
	}
	if (data->str[*i])
		data->env_str[(*j)++] = data->str[(*i)++];
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

void	change_env(t_parsedata *data, t_list *env)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (data->str[i])
	{
		if (data->str[i] == '$')
		{
			if (ft_isalpha(data->str[++i]) || data->str[i] == '_'
				|| data->str[i] == '?')
				change_value(data, &i, &j, env);
			else
				data->env_str[j++] = '$';
		}
		else if (ft_isquote(data->str[i]) == 2)
			change_env_quote(data, &i, &j, env);
		else if (ft_isquote(data->str[i]) == 1)
			no_change_vlaue(data->str, data->env_str, &i, &j);
		else
			data->env_str[j++] = data->str[i++];
	}
}
