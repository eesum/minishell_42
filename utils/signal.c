/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 08:34:57 by seohyeki          #+#    #+#             */
/*   Updated: 2024/03/28 17:56:52 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"
#include <stdio.h>
#include <readline/readline.h>
#include <signal.h>

volatile sig_atomic_t	g_sig;

void	sig_update(t_list *env)
{
	if (g_sig == 1)
	{
		g_sig = 0;
		update_env("?", "1", env);
	}
}

void	parent_sig(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		if (rl_on_new_line() < 0)
			error_exit("readline error", 0, 0, EXIT_FAILURE);
		rl_replace_line("", 1);
		rl_redisplay();
		g_sig = 1;
	}
	else
		return ;
}

void	heredoc_sig(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		if (rl_on_new_line() < 0)
			error_exit("readline error", 0, 0, EXIT_FAILURE);
		rl_replace_line("", 1);
		exit(100);
	}
}
