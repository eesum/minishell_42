/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohyeki <seohyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 20:09:37 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/23 15:50:31 by seohyeki         ###   ########.fr       */
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
	pid_t	*pid;
	char	**path;
	t_list	*pipe;
	t_list	*env;
	int		doc_cnt;
	int		*doc_fd;
	char	**eof_arr;
	char	**file_arr;
}				t_execdata;

/*signal*/
void	set_sig_term(void sigint(int), void sigquit(int), int term);
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
int		parsing(t_parsedata *parse, t_execdata *exec);

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
int		exec_cmd(char **cmd, t_list *env, int pipe_flag);
int		only_builtin(t_execdata *data);
void	wait_and_update_exit_code(pid_t *pid, t_list *env);
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
void	exec_exit(char **cmd, int pipe_flag);

/*free*/
void	free_token(void *token);
void	free_tokens_in_pipe(void *node);
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
char	*ft_strjoin_sep(char const *s1, char const *s2, char const *sep);
char	*find_env(char *name, t_list *env);
void	update_env(char *name, char *value, t_list *env);
int		check_cmd_option(char **cmd);
int		check_valid_name(char *cmd, char *arg, char sep);
int		ft_isspace(char c);
t_list	*ft_findlst_by_index(t_list *lst, int i);
void	restore_fds(t_execdata *data, int input_fd, int output_fd);

#endif