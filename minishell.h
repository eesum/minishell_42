/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 20:09:37 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/11 14:04:05 by sumilee          ###   ########.fr       */
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
# include "libft/libft.h"

typedef struct s_token
{
	char			*str;
	int				type;
}				t_token;

typedef struct s_execdata
{
	int		cmd_cnt;
	int		index;
	int		fd[2][2];
	pid_t	pid;
	char	**path;
	int		status;
	t_list	*pipe;
	t_list	*env;
	int		doc_cnt;
	int		*doc_fd;
	char	**doc_arr;
}				t_execdata;

void	error_exit(char *msg, char *cmd, char *arg, int code);
void	*ft_malloc_err(size_t size);
char	*ft_strdup_err(const char *s1);
char    *ft_strndup(char *origin, int count);
t_token *ft_make_newtoken(char *str, int type);
void	 parsing(char *str, t_list **head);

#endif