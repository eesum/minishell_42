/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:00:52 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/23 17:31:01 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

void	exec(t_execdata *data);
void	init_token_flags(t_execdata *data);
void	before_heredoc(t_execdata *data);
int		here_document(t_execdata *data);
int		check_file_open(t_list *pipe_tokens);
void	wait_and_update_exit_code(pid_t *pid, t_list *env);

/*command*/
char	**cmd_to_arr(t_list *pipe_tokens);
void	exec_in_child(t_execdata *data, int i);
int		is_builtin(char *cmd);
int		exec_cmd(char **cmd, t_list *env, int pipe_flag);
void	exec_general_cmd(char **cmd, t_list *env);
void	end_exec(t_execdata *data);

/*fd utils*/
int		open_last_input(t_list *pipe, char **file_arr);
int		open_last_output(t_list *pipe);
void	dup_fds(t_execdata *data, int input_fd, int output_fd);
void	restore_fds(t_execdata *data, int input_fd, int output_fd);

/*etc utils*/
char	**lst_to_envp(t_list *env);
void	update_env(char *name, char *value, t_list *env);
int		check_valid_name(char *cmd, char *arg, char sep);
char	*ft_itoa_err(int n);;

#endif