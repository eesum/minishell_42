/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohyeki <seohyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:18:56 by seohyeki          #+#    #+#             */
/*   Updated: 2024/03/14 19:42:47 by seohyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tokenlst(t_list *node)
{
	t_token *token;

	token = (t_token *)node->content;
	free(token->str);
	free(token);
	free(node);
}