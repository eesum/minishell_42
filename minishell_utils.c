/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohyeki <seohyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:27:17 by seohyeki          #+#    #+#             */
/*   Updated: 2024/03/09 18:46:54 by seohyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup(char *origin, int count)
{
	char 	*str;
	size_t	i;

	str = (char *)malloc(sizeof(char) + (count + 1));
	//malloc 실패 처리
	str[count] = '\0';
	i = 0;
	while (*origin && count)
	{
		str[i] = *origin;
		i++;
		origin++;
		count--;
	}
	return(str);
}

t_token	*ft_make_newtoken(char *str, int type)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	//malloc 실패
	if (new == NULL)
		return (NULL);
	new->str = str;
	new->type = type;
	new->next = 0;
	return (new);
}

t_token	*ft_lstlast(t_token *lst)
{
	if (lst)
	{
		while (lst->next != NULL)
			lst = lst->next;
	}
	return (lst);
}

void ft_lstadd_back(t_token **head, t_token *new)
{
	t_token	*last;

	if (!new || !head)
		return ;
	if (*head == NULL)
		*head = new;
	else
	{
		last = ft_lstlast(*head);
		last->next = new;
	}
}