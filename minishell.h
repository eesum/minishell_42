/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 20:09:37 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/13 15:52:49 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define TYPE_DEFAULT 0
# define TYPE_HEREDOC 1
# define TYPE_INPUT 2
# define TYPE_OUTPUT_T 3
# define TYPE_OUTPUT_A 4
# define TYPE_PIPE 5

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include "libft/libft.h"

typedef struct s_token
{
	char			*str;
	int				type;
}				t_token;

typedef struct s_execdata
{
	int		pipe_cnt;
	int		index;
	int		fd[2][2];
	pid_t	pid;
	char	**path;
	t_list	*pipe;
	t_list	*env;
	int		doc_cnt;
	int		*doc_fd;
	char	**eof_arr;
	char	**file_arr;
}				t_execdata;

void	error_exit(char *msg, char *cmd, char *arg, int code);
void	error_msg_only(char *msg, char *cmd, char *arg);
void	*ft_malloc_err(size_t size);
char	*ft_strdup_err(const char *s1);
char    *ft_strndup(char *origin, int count);
t_token *ft_make_newtoken(char *str, int type);
void	 parsing(char *str, t_list **head);
char	*ft_strjoin_sep(char const *s1, char const *s2, char const *sep);
char	*find_env(char *name, t_list *env);
void	update_env(char *name, char *value, t_list *env);
void	check_cmd_option(char **cmd);
int		check_valid_name(char *arg, char sep);
void	wait_and_update_exit_code(int doc_cnt, t_list *env);
void	here_document(t_execdata *data);
int		is_builtin(char *cmd);

#endif