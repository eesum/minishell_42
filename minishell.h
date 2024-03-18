/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 20:09:37 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/18 14:12:00 by sumilee          ###   ########.fr       */
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
	char	*str;
	int		type;
	int		hd_index;
	int		redirect_flag;
}				t_token;

typedef struct s_execdata
{
	int		pipe_cnt;
	int		index;
	int		fd[2][2];
	int		tmp_fd[2];
	pid_t	pid;
	char	**path;
	t_list	*pipe;
	t_list	*env;
	int		doc_cnt;
	int		*doc_fd;
	char	**eof_arr;
	char	**file_arr;
}				t_execdata;

/*parse*/
char	*get_env_name(char *str);
void	change_env(char *str, t_list *envlist, char *new_str);
char	*parsing_env(char *str, t_list *envlist);
void	split_token(t_list **head, char *str);
void	delete_quote(t_list **head);
void	check_token(t_list **head, t_list **pipe);

/*exec*/
void	init_token_flags(t_execdata *data);
t_list *envp_to_lst(char **envp);
int		count_pipe(t_execdata *data);
int		check_file_open(t_list *pipe_cntnt);
int		open_last_input(t_list *pipe, char **file_arr);
int		open_last_output(t_list *pipe);
void	dup_fds(t_execdata *data, int input_fd, int output_fd);
char	**cmd_to_arr(t_list *pipe);
char	**lst_to_envp(t_list *env);
char	**split_path(char **envp);
char	*find_cmd(char **path, char *cmd);
void	exec_general_cmd(char **cmd, t_list *env);
int		exec_cmd(char **cmd, t_list *env);
int		only_builtin(t_execdata *data);
void	wait_and_update_exit_code(int wait_cnt, t_list *env);
void	here_document(t_execdata *data);
int		is_builtin(char *cmd);
void	exec_in_child(t_execdata *data, int i);

/*builtin*/
int		exec_echo(char **cmd);
int		exec_cd(char **cmd, t_list *env);
int		exec_pwd(char **cmd);
int		exec_export(char **cmd, t_list *env);
int		exec_unset(char **cmd, t_list *env);
int		exec_env(char **cmd, t_list *env);
void	exec_exit(char **cmd);

/*free*/
void	ft_free_tokenlst(t_list *node);
void	free_arr(char **arr);

/*error*/
void	error_exit(char *msg, char *cmd, char *arg, int code);
void	error_msg_only(char *msg, char *cmd, char *arg);
void	*ft_malloc_err(size_t size);
char	*ft_strdup_err(const char *s1);
char	*ft_substr_err(char const *s, unsigned int start, size_t len);
char	*ft_itoa_err(int n);
char	*ft_strjoin_err(char const *s1, char const *s2);

/*utils*/
void	ft_strcpy(char *dest, const char *src);
char	*ft_strjoin_sep(char const *s1, char const *s2, char const *sep);
char	*find_env(char *name, t_list *env);
void	update_env(char *name, char *value, t_list *env);
void	check_cmd_option(char **cmd);
int		check_valid_name(char *cmd, char *arg, char sep);
int		ft_ispipe(char c);
int		ft_isspace(char c);
int 	ft_isredirect(char c);
int		ft_isquote(char c);
char    *ft_strndup(char *origin, int count);
t_list	*ft_findlst_by_index(t_list *lst, int i);
void	restore_fds(t_execdata *data, int input_fd, int output_fd);

/////////////////임시
void	debug_print(char *file, int line, const char *func);

#endif