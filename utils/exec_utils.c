/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohyeki <seohyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:29:18 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/28 15:58:59 by seohyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "util.h"
#include <stdio.h>
#include <sys/signal.h>
#include <sys/wait.h>

int	wait_and_update_exit_code(pid_t *pid)
{
	int		i;
	int		status;
	pid_t	wait_pid;
	int		exit_code;

	i = 0;
	while (pid && pid[i])
	{
		wait_pid = waitpid(pid[i], &status, 0);
		if (wait_pid < 0)
			error_exit("wait error", 0, 0, EXIT_FAILURE);
		else if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGQUIT)
				printf("Quit: 3");
			printf("\n");
			exit_code = 128 + WTERMSIG(status);
		}
		i++;
	}
	set_sig_term(parent_sig, SIG_IGN, 0);
	return (exit_code);
}

char	**lst_to_envp(t_list *env)
{
	t_list	*cur;
	int		cnt;
	char	**envp;

	cnt = 0;
	cur = env;
	while (cur != NULL)
	{
		cnt++;
		cur = cur->next;
	}
	envp = ft_malloc_err(sizeof(char *) * (cnt + 1));
	envp[cnt] = NULL;
	cnt = 0;
	cur = env;
	while (cur != NULL)
	{
		envp[cnt] = ft_strdup_err((char *)cur->content);
		cnt++;
		cur = cur->next;
	}
	return (envp);
}

int	check_valid_name(char *cmd, char *arg, char sep)
{
	int	i;

	if (arg && arg[0] != '_' && ft_isalpha(arg[0]) == 0)
	{
		error_msg_only("not a valid identifier", cmd, arg);
		return (-1);
	}
	i = 1;
	while (arg && arg[i] && arg[i] != sep)
	{
		if (arg[i] != '_' && ft_isalnum(arg[i]) == 0)
		{
			error_msg_only("not a valid identifier", cmd, arg);
			return (-1);
		}
		i++;
	}
	return (i);
}
