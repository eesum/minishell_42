/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:03:50 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/23 17:44:32 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"
#include <unistd.h>

static void	delete_tmpfile(t_execdata *data)
{
	int	i;

	i = 0;
	while (data->file_arr && data->file_arr[i])
	{
		if (access(data->file_arr[i], F_OK) == 0
			&& unlink(data->file_arr[i]) < 0)
			error_msg_only("file unlink failed", data->file_arr[i], 0);
		i++;
	}
}

void	end_exec(t_execdata *data)
{
	delete_tmpfile(data);
	free_arr(data->eof_arr);
	free_arr(data->file_arr);
	if (data->doc_fd != NULL)
		free(data->doc_fd);
	if (data->pid != NULL)
		free(data->pid);
	ft_lstclear(&data->pipe, free_tokens_in_pipe);
}
