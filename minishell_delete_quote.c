/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_delete_quote.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohyeki <seohyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:37:49 by seohyeki          #+#    #+#             */
/*   Updated: 2024/03/14 18:37:03 by seohyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void count_without_quote(char *str, size_t *len)
{
	size_t	i;
	char	c;
	
	i = 0;
	while (str[i])
	{
		if (ft_isquote(str[i]))
		{
			c = str[i++];
			while (str[i] != c && str[i])
			{
				len++;
				i++;
			}
			if (str[i])
				i++;
		}
		else
		{
			i++;
			len++;
		}
	}
}

static char *realloc_without_quote(char *origin, size_t size)
{
	size_t	i;
	size_t	j;
	char	*new;
	char	c;

	i = 0;
	j = 0;
	new = (char *)ft_malloc_err(sizeof(char) * (size + 1));
	new[size] = '\0';
	while (origin[i])
	{
		if (ft_isquote(origin[i]))
		{
			c = origin[i++];
			while (origin[i] != c)
			{
				new[j++] = origin[i++];
			}
			i++;
		}
		else
			new[j++] = origin[i++];
	}
	free(origin);
	return (new);
}

void	delete_quote(t_list **head)
{
	size_t	len;
	t_token	*token;
	t_list	*curr;

	curr = *head;
	while (curr)
	{
		len = 0;
		token = (t_token *)curr->content;
		count_without_quote(token->str, &len);
		if (ft_strlen(token->str) != len)
			token->str = realloc_without_quote(token->str, len);
		curr = curr->next;
	}
}
