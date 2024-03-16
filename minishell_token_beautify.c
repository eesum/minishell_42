/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_token_beautify.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohyeki <seohyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:51:53 by seohyeki          #+#    #+#             */
/*   Updated: 2024/03/16 22:17:47 by seohyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	delete_redirection_loop(t_list **head, t_list **cur, t_list **pre)
{
	t_token	*token;
	t_list	*tmp;

	token = (t_token *)(*cur)->content;
	if (((t_token *)(*cur)->next->content)->type != 0)
	{
		ft_tokenlst_free(head);
		return (1);
	}
	((t_token *)(*cur)->next->content)->type = token->type;
	if ((*cur) == *head)
		*head = (*cur)->next;
	else
		(*pre)->next = (*cur)->next;
	tmp = (*cur);
	(*cur) = (*cur)->next;
	ft_token_free(tmp);
	return (0);
}

static int	delete_redirection(t_list **head)
{
	t_token	*token;
	t_list	*cur;
	t_list	*pre;
	t_list	*tmp;

	cur = *head;
	while (cur)
	{
		token = (t_token *)cur->content;
		if (1 <= token->type && token->type <= 4)
		{
			if (delete_redirection_loop(head, &cur, &pre))
				return (1);
		}
		pre = cur;
		cur = cur->next;
	}
	return (0);
}

static void	split_pipe(t_list **head, t_list **pipe)
{
	t_list	*curr;
	t_list	*prev;
	t_list	*temp;

	curr = *head;
	prev = NULL;
	ft_lstadd_back(pipe, ft_lstnew(curr));
	while (curr)
	{
		if (((t_token *)curr->content)->type == TYPE_PIPE)
		{
			ft_lstadd_back(pipe, ft_lstnew(curr->next));
			temp = curr;
			prev->next = NULL;
			prev = NULL;
			curr = curr->next;
			ft_token_free(temp);
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}

void	beautify_token(t_list **head, t_list **pipe)
{
	t_list	*node;

	if (*head == NULL)
		return ;
	node = *head;
	if (((t_token *)node->content)->type == TYPE_PIPE
		|| ((t_token *)ft_lstlast(node)->content)->type == TYPE_PIPE)
	{
		ft_tokenlst_free(head);
		return ;
	}
	delete_quote(head);
	if (delete_redirection(head))
		return ;
	split_pipe(head, pipe);
}
