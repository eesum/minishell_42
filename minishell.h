/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 20:09:37 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/20 20:48:34 by sumilee          ###   ########.fr       */
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
# define SYNTAX_ERROR 1

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <signal.h>
# include <termios.h>
# include <dirent.h>
# include <sys/types.h>
# include "libft/libft.h"

typedef struct s_token
{
	char	*str;
	int		type;
	int		hd_index;
	int		redirect_flag;
}				t_token;

typedef struct s_parsedata
{
	char	*str;
	char	*env_str;
	t_list	*token_head;
}				t_parsedata;

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

void	exec(t_execdata *data);

/*signal*/
void	set_terminal_print_off(void);
void	set_terminal_print_on(void);
void	parent_sig(int signum);
void	heredoc_sig(int signum);

/*parse*/
char	*get_env_name(char *str);
void	count_total_len(char *str, t_list *env, size_t *len);
void	change_default(t_parsedata *data, size_t *i, size_t *j, t_list *env);
void	change_quote(t_parsedata *data, size_t *i, size_t *j, t_list *env);
void	parsing_env(t_parsedata *data, t_list *env);
int		check_token_type(char *str);
int		split_token(t_list **head, char *str);
void	delete_quote(t_list **head);
int		beautify_token(t_list **head, t_list **pipe);

/*exec*/
void	exec(t_execdata *data);
void	init_token_flags(t_execdata *data);
t_list	*envp_to_lst(char **envp);
int		count_pipe(t_execdata *data);
int		check_file_open(t_list *pipe_tokens);
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
int		here_document(t_execdata *data);
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
void	free_token(void *token);
void	free_tokens_in_pipe(void *node);
void	free_arr(char **arr);
void	ft_token_free(t_list *node);
void	ft_tokenlst_free(t_list **lst);

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
int		check_cmd_option(char **cmd);
int		check_valid_name(char *cmd, char *arg, char sep);
int		ft_ispipe(char c);
int		ft_isspace(char c);
int		ft_isredi(char c);
int		ft_isquote(char c);
char	*ft_strndup(char *origin, int count);
t_list	*ft_findlst_by_index(t_list *lst, int i);
void	restore_fds(t_execdata *data, int input_fd, int output_fd);
void	exit_after_print(int exit_code);

/////////////////임시
void	debug_print(char *file, int line, const char *func);

#endif