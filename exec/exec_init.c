/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:51:25 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/23 15:02:18 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_heredoc(t_list *pipe)
{
	t_list	*cur;
	int		doc_cnt;

	doc_cnt = 0;
	cur = pipe;
	while (cur != NULL)
	{
		((t_token *)cur->content)->hd_index = -1;
		if (((t_token *)cur->content)->type == TYPE_HEREDOC)
		{
			((t_token *)cur->content)->hd_index = doc_cnt;
			doc_cnt++;
		}
		cur = cur->next;
	}
	return (doc_cnt);
}

static void	flag_last_redirection(t_list *pipe)
{
	t_list	*cur;
	t_list	*last_input;
	t_list	*last_output;

	cur = pipe;
	last_input = NULL;
	last_output = NULL;
	while (cur != NULL)
	{
		((t_token *)cur->content)->redirect_flag = 0;
		if (((t_token *)cur->content)->type == TYPE_INPUT || \
			((t_token *)cur->content)->type == TYPE_HEREDOC)
			last_input = cur;
		else if (((t_token *)cur->content)->type == TYPE_OUTPUT_T || \
			((t_token *)cur->content)->type == TYPE_OUTPUT_A)
			last_output = cur;
		cur = cur->next;
	}
	if (last_input != NULL)
		((t_token *)last_input->content)->redirect_flag = 1;
	if (last_output != NULL)
		((t_token *)last_output->content)->redirect_flag = 2;
}

void	init_token_flags(t_execdata *data)
{
	t_list	*pipe_cur;

	pipe_cur = data->pipe;
	data->doc_cnt = 0;
	while (pipe_cur != NULL)
	{
		data->doc_cnt += count_heredoc(pipe_cur->content);
		flag_last_redirection(pipe_cur->content);
		pipe_cur = pipe_cur->next;
	}
}
