/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:12:42 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/23 17:42:56 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../libft/libft.h"

int		check_cmd_option(char **cmd);
int		exec_echo(char **cmd);
int		exec_cd(char **cmd, t_list *env);
int		exec_pwd(char **cmd);
int		exec_env(char **cmd, t_list *env);
int		exec_export(char **cmd, t_list *env);
int		exec_unset(char **cmd, t_list *env);
void	exec_exit(char **cmd, int pipe_flag);

#endif