/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:36:20 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/14 18:12:00 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_file_open(t_list *pipe_cntnt)
{
	t_list	*cur;
	int		fd;

	cur = pipe_cntnt;
	while (cur != NULL)
	{
		if (((t_token *)cur->content)->type == TYPE_INPUT)
		{
			if (access(((t_token *)cur->content)->str, F_OK) != 0)
			{
				error_msg_only("No such file or directory", ((t_token *)cur->content)->str, 0);
				return (-1);
			}
			else if (access(((t_token *)cur->content)->str, R_OK) != 0)
			{
				error_msg_only("Permission denied", ((t_token *)cur->content)->str, 0);
				return (-1);
			}
		}
		if (((t_token *)cur->content)->type == TYPE_OUTPUT_A)
		{
			fd = open(((t_token *)cur->content)->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
			{
				error_msg_only("Permission denied", ((t_token *)cur->content)->str, 0);
				return (-1);
			}
			close(fd);
		}
		if (((t_token *)cur->content)->type == TYPE_OUTPUT_T)
		{
			fd = open(((t_token *)cur->content)->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
			{
				error_msg_only("Permission denied", ((t_token *)cur->content)->str, 0);
				return (-1);
			}
			close(fd);
		}
		cur = cur->next;
	}
	return (0);
}

// void	find_last_redirect(t_execdata *data, char **in, char **out_t, char **out_a)
// {
// 	t_list	*cur;

// 	cur = data->pipe->content;
// 	while (cur != NULL)
// 	{
// 		if (((t_token *)cur->content)->type == TYPE_INPUT)
// 		{
// 			*in = ((t_token *)cur->content)->str;
// 			printf("in: %s\n", *in);
// 		}
// 		else if (((t_token *)cur->content)->type == TYPE_HEREDOC)
// 			*in = data->file_arr[((t_token *)cur->content)->hd_index];
// 		else if (((t_token *)cur->content)->type == TYPE_OUTPUT_A)
// 		{
// 			*out_a = ((t_token *)cur->content)->str;
// 			*out_t = NULL;
// 		}
// 		else if (((t_token *)cur->content)->type == TYPE_OUTPUT_T)
// 		{
// 			*out_t = ((t_token *)cur->content)->str;
// 			*out_a = NULL;
// 		}
// 		cur = cur->next;
// 	}
// }


