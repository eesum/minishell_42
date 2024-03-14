/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_token_check.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohyeki <seohyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:51:53 by seohyeki          #+#    #+#             */
/*   Updated: 2024/03/14 20:08:07 by seohyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			ft_free_tokenlst(temp);
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}


static void delete_redirection(t_list **head)
{
	t_list	*curr;
	t_list	*prev;
	t_list	*temp;
	
	curr = *head;
	prev = NULL;
	while (curr)
	{
		if (1 <= ((t_token *)curr->content)->type && ((t_token *)curr->content)->type <= 4) 
		{
			if (((t_token *)curr->next->content)->type != 0)
				error_exit ("syntax error", 0, 0, 1);
			((t_token *)curr->next->content)->type = ((t_token *)curr->content)->type;
			temp = curr;
			if (prev)
			{
				prev->next = curr->next;
				prev = curr->next;
			}
			else
				*head = curr->next;
			curr = curr->next->next;
			ft_free_tokenlst(temp);
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}

void	check_token(t_list **head, t_list **pipe)
{
	t_list *node;

	node = *head;
	//fist,last node pipe
	if (((t_token *)node->content)->type == TYPE_PIPE || ((t_token *)ft_lstlast(node)->content)->type == TYPE_PIPE)
		error_exit ("syntax error", 0, 0, 1);
	delete_quote(head);
	delete_redirection(head);
	split_pipe(head, pipe);
}
