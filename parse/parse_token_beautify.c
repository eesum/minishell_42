/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_beautify.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:51:53 by seohyeki          #+#    #+#             */
/*   Updated: 2024/03/26 02:46:09 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "util.h"

static int	delete_redirection_node(t_list **head, t_list **cur, t_list **pre)
{
	t_token	*token;
	t_list	*tmp;

	token = (t_token *)(*cur)->content;
	if (((t_token *)(*cur)->next->content)->type != 0)
	{
		ft_lstclear(head, free_token);
		return (SYNTAX_ERROR);
	}
	((t_token *)(*cur)->next->content)->type = token->type;
	if ((*cur) == *head)
		*head = (*cur)->next;
	else
		(*pre)->next = (*cur)->next;
	tmp = (*cur);
	(*cur) = (*cur)->next;
	ft_lstdelone(tmp, free_token);
	return (0);
}

static int	delete_redirection(t_list **head)
{
	t_token	*token;
	t_list	*cur;
	t_list	*pre;

	cur = *head;
	while (cur)
	{
		token = (t_token *)cur->content;
		if (1 <= token->type && token->type <= 4)
		{
			if (delete_redirection_node(head, &cur, &pre))
				return (SYNTAX_ERROR);
		}
		pre = cur;
		cur = cur->next;
	}
	return (0);
}

static void	split_pipe(t_list **head, t_list **pipe)
{
	t_list	*cur;
	t_list	*pre;
	t_list	*tmp;

	cur = *head;
	pre = NULL;
	ft_lstadd_back(pipe, ft_lstnew(cur));
	while (cur)
	{
		if (((t_token *)cur->content)->type == TYPE_PIPE)
		{
			ft_lstadd_back(pipe, ft_lstnew(cur->next));
			tmp = cur;
			pre->next = NULL;
			pre = NULL;
			cur = cur->next;
			ft_lstdelone(tmp, free_token);
		}
		else
		{
			pre = cur;
			cur = cur->next;
		}
	}
}

int	beautify_token(t_list **head, t_list **pipe)
{
	t_list	*node;

	if (*head == NULL)
		return (1);
	node = *head;
	if (((t_token *)node->content)->type == TYPE_PIPE
		|| ((t_token *)ft_lstlast(node)->content)->type == TYPE_PIPE)
	{
		ft_lstclear(head, free_token);
		return (1);
	}
	delete_quote(head);
	if (delete_redirection(head))
		return (1);
	split_pipe(head, pipe);
	return (0);
}
