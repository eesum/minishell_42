/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_general_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:34:33 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/18 14:19:40 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**lst_to_envp(t_list *env)
{
	t_list	*cur;
	int		cnt;
	char	**envp;

	cnt = 0;
	cur = env;
	while (cur != NULL)
	{
		cnt++;
		cur = cur->next;
	}
	envp = ft_malloc_err(sizeof(char *) * (cnt + 1));
	envp[cnt] = NULL;
	cnt = 0;
	cur = env;
	while (cur != NULL)
	{
		envp[cnt] = ft_strdup_err((char *)cur->content);
		cnt++;
		cur = cur->next;
	}
	return (envp);
}

char	**split_path(char **envp)
{
	int		i;
	char	**path;

	i = 0;
	path = NULL;
	while (envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
		{
			path = ft_split(&envp[i][5], ':');
			if (path == NULL)
				error_exit("malloc failed.", 0, 0, EXIT_FAILURE);
			break ;
		}
		i++;
	}
	return (path);
}

char	*find_cmd(char **path, char *cmd)
{
	char	*path_join;
	int		i;

	path_join = NULL;
	i = 0;
	while (path[i])
	{
		path_join = ft_strjoin_sep(path[i], cmd, "/");
		if (path_join == NULL)
			error_exit("path / command error.", 0, 0, EXIT_FAILURE);
		if (access(path_join, X_OK) == 0)
			break ;
		else
			free(path_join);
		path_join = NULL;
		i++;
	}
	return (path_join);
}

void	exec_general_cmd(char **cmd, t_list *env)
{
	char	**envp;
	char	**path;
	char	*path_join;
	int		i;

	path_join = NULL;
	envp = lst_to_envp(env);
	path = split_path(envp);
	if (cmd[0] != NULL && path != NULL)
		path_join = find_cmd(path, cmd[0]);
	if (cmd[0] == NULL)
		error_exit("command not found", 0, 0, EXIT_FAILURE);
	if (path_join == NULL)
		error_exit("command not found", cmd[0], 0, EXIT_FAILURE);
	i = 0;
	while (path[i])
	{
		free(path[i]);
		path[i] = NULL;
		i++;
	}
	if (execve(path_join, cmd, envp) < 0)
		error_exit("exec failed.", 0, 0, EXIT_FAILURE);
}