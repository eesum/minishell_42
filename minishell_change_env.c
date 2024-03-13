/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_change_env.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohyeki <seohyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:34:51 by seohyeki          #+#    #+#             */
/*   Updated: 2024/03/13 21:01:06 by seohyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	no_interpret(char *str, char *new, size_t *i, size_t *j)
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

static void	change_value(char *new, char *name, size_t *j, t_list *envlist)
{
	char	*value;

	value = find_env(name, envlist);
	ft_strcpy(new + (*j), value);
	(*j) += ft_strlen(value);
	free(value);
}

void	change_env(char *str, t_list *envlist, char *new_str)
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
			i++;
			if (ft_isalpha(str[i]) || str[i] == '_')
			{
				name = get_env_name(str + i);
				change_value(new_str, name, &j, envlist);
				i += ft_strlen(name);
				free(name);
			}
			else
				new_str[j++] = '$';
		}
		else if (str[i] == '\'')
			no_interpret(str, new_str, &i, &j);
		else
			new_str[j++] = str[i++];
	}
}
