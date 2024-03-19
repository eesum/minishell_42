/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohyeki <seohyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:18:56 by seohyeki          #+#    #+#             */
/*   Updated: 2024/03/19 18:02:09 by seohyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_token_free(t_list *node)
{
	t_token	*token;

	token = (t_token *)node->content;
	free(token->str);
	free(token);
	free(node);
}

void	ft_tokenlst_free(t_list **lst)
{
	t_list	*tmp;
	t_list	*cur;

	cur = *lst;
	while (cur)
	{
		tmp = cur;
		cur = cur->next;
		ft_token_free(tmp);
	}
	*lst = NULL;
}

void	ft_free_t(t_token **t)
{
	free((*t)->str);
	free(*t);
}

void	ft_free_l(t_list **lst)
{
	t_list	*tmp;

	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		ft_free_t(tmp->content);
		free(tmp);
	}
}

void	ft_free_p(t_list **pipe)
{
	t_list	*tmp;

	while (*pipe)
	{
		tmp = *pipe;
		*pipe = (*pipe)->next;
		ft_free_l(tmp->content);
		free(tmp);
	}
}
