/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 20:09:37 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/10 14:00:28 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_pipe
{
	t_token			*addr;
	struct s_pipe	*next;
}				t_pipe;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*next;
}				t_token;

typedef struct s_env
{
	char			*str;
	struct s_env	*next;
}				t_env;

typedef struct s_execdata
{
	int		cmd_cnt;
	int		index;
	int		fd[2][2];
	pid_t	pid;
	char	**path;
	int		status;
}				t_execdata

#endif