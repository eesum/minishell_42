/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:50:23 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/29 17:36:41 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "stdio.h"
#include <readline/readline.h>
#include <readline/history.h>

char	*prompt_shell(t_list *env)
{
	char	*result;

	set_sig_term(sig_handler, SIG_IGN, 0);
	set_terminal_echo_on();
	rl_event_hook = ctrl_c_new_prompt;
	result = readline("minishell $ \001\033[s\002");
	signal(SIGINT, SIG_IGN);
	sig_update(env);
	if (result == NULL)
		printf("\033[u\033[1B\033[1A");
	if (result && *result)
		add_history(result);
	return (result);
}

char	*prompt_heredoc(void)
{
	char	*result;

	set_sig_term(sig_handler, SIG_IGN, 0);
	rl_event_hook = ctrl_c_heredoc;
	result = readline("> \001\033[s\002");
	signal(SIGINT, SIG_IGN);
	if (result == NULL)
		printf("\033[u\033[1B\033[1A");
	return (result);
}
