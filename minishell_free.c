/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohyeki <seohyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:18:56 by seohyeki          #+#    #+#             */
/*   Updated: 2024/03/20 05:57:01 by seohyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(void *token)
{
	t_token	*token_node;

	token_node = (t_token *)token;
	if (token_node != NULL)
	{
		if (token_node->str != NULL)
			free(token_node->str);
		free(token_node);
	}
}

void	free_tokens_in_pipe(void *node)
{
	t_list	*pipe_tokens;

	pipe_tokens = (t_list *)node;
	if (pipe_tokens != NULL)
		ft_lstclear(&pipe_tokens, free_token);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (arr == NULL)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

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
