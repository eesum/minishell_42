/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:29:18 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/23 17:17:12 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"
#include <stdio.h>
#include <sys/wait.h>

void	wait_and_update_exit_code(pid_t *pid, t_list *env)
{
	int		i;
	int		status;
	pid_t	wait_pid;
	char	*exit_code_char;

	i = 0;
	while (pid && pid[i])
	{
		wait_pid = waitpid(pid[i], &status, 0);
		if (wait_pid < 0)
			error_exit("wait error", 0, 0, EXIT_FAILURE);
		else if (WIFEXITED(status))
			exit_code_char = ft_itoa_err(WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
		{
			printf("\n");
			exit_code_char = ft_itoa_err(128 + WTERMSIG(status));
		}
		update_env("?", exit_code_char, env);
		free(exit_code_char);
		i++;
	}
	set_sig_term(parent_sig, SIG_IGN, 0);
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

	if (arg && arg[0] != 95 && \
		(arg[0] < 65 || (arg[0] > 90 && arg[0] < 97) || arg[0] > 122))
	{
		error_msg_only("not a valid identifier", cmd, arg);
		return (-1);
	}
	i = 1;
	while (arg && arg[i] && arg[i] != sep)
	{
		if (arg[i] != 95 && \
			(arg[i] < 48 || (arg[i] > 57 && arg[i] < 65) || \
			(arg[i] > 90 && arg[i] < 97) || arg[i] > 122))
		{
			error_msg_only("not a valid identifier", cmd, arg);
			return (-1);
		}
		i++;
	}
	return (i);
}
