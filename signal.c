/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 08:34:57 by seohyeki          #+#    #+#             */
/*   Updated: 2024/03/20 21:18:56 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_terminal_print_off(void)
{
	struct termios	term;

	tcgetattr(1, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(1, 0, &term);
}

void	set_terminal_print_on(void)
{
	struct termios	term;

	tcgetattr(1, &term);
	term.c_lflag |= (ECHOCTL);
	tcsetattr(1, 0, &term);
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