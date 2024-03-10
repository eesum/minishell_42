/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 13:38:45 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/10 16:32:27 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_exit(char *msg, char *cmd, char *arg, int code)
{
	if (msg != NULL)
	{
		ft_putstr_fd("pipex: ", 2);
		if (cmd != NULL)
		{
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": ", 2);
		}
		if (arg != NULL)
		{
			ft_putstr_fd(arg, 2);
			ft_putstr_fd(": ", 2);
		}
		ft_putstr_fd(msg, 2);
		write(2, "\n", 1);
	}
	exit(code);
}


void exec()
{
	//here doc 실행
		// heredoc 개수 확인
	// heredoc 개수 1개 이상이면, 그 동안 while 돌면서 순서대로 limiter에 지금 단어 집어넣고
	// 그 limiter와 같은거 나올때까지 memcmp?? 하면서 파일 열고 대기....
	// 파일 이름 겹치는 거 어떻게 해결하지???? random한 파일 제목 생성 같은거 해야하나,...?
	// 현재시간 ? 히어독 
	

	// 파이프(커맨드 단위) 몇개 있는지 확인
	//있으면 그때부터 while 돎

	// 


	// wait childe
	// heredoc 파일들 다 지우기??????
}