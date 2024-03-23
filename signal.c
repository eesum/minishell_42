/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 08:34:57 by seohyeki          #+#    #+#             */
/*   Updated: 2024/03/23 18:29:51 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <signal.h>
#include <termios.h>

static void	set_terminal_print_off(void)
{
	struct termios	term;

	tcgetattr(1, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(1, 0, &term);
}

static void	set_terminal_print_on(void)
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

void	set_sig_term(void sigint(int), void sigquit(int), int term)
{
	signal(SIGINT, sigint);
	signal(SIGQUIT, sigquit);
	if (term == 1)
		set_terminal_print_on();
	else if (term == 0)
		set_terminal_print_off();
}
