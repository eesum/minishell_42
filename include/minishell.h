/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 20:09:37 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/23 17:43:35 by sumilee          ###   ########.fr       */
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

# include "../libft/libft.h"

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

/*free*/
void	free_token(void *token);
void	free_tokens_in_pipe(void *node);
void	free_arr(char **arr);

/*error*/
void	error_exit(char *msg, char *cmd, char *arg, int code);
void	error_msg_only(char *msg, char *cmd, char *arg);

/*utils*/
void	*ft_malloc_err(size_t size);
char	*ft_strjoin_sep(char const *s1, char const *s2, char const *sep);
char	*ft_strdup_err(const char *s1);
int		ft_isspace(char c);
t_list	*envp_to_lst(char **envp);
char	*find_env(char *name, t_list *env);
void	update_env(char *name, char *value, t_list *env);

#endif