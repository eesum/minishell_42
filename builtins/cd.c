/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 20:14:04 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/19 16:32:37 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	change_dir(char *dest_path, char *current_path, char *arg, t_list *env)
{
	char	*new_pwd;

	if (chdir(dest_path) < 0)
	{
		if (errno == EACCES || errno == EFAULT)
			error_msg_only("Permission denied", "cd", arg);
		else if (errno == ENOENT)
			error_msg_only("No such file or directory", "cd", arg);
		else if (errno == ENOTDIR)
			error_msg_only("Not a directory", "cd", arg);
		else
			error_msg_only("Error occured", "cd", arg);
		free(dest_path);
		free(current_path);
		return (-1);
	}
	new_pwd = getcwd(NULL, 0);
	update_env("OLDPWD", current_path, env);
	update_env("PWD", new_pwd, env);
	free(new_pwd);
	return (0);
}

int	to_directory(char *path, char *current_path, char **cmd, t_list *env)
{
	char	*dest_path;

	dest_path = find_env(path, env);
	if (dest_path == NULL)
	{
		error_msg_only("Environment variables not set", 0, 0);
		return (-1);
	}
	if (dest_path && dest_path[0] == '\0')
	{
		free(dest_path);
		error_msg_only("not set", cmd[0], path);
		return (-1);
	}
	if (change_dir(dest_path, current_path, 0, env) < 0)
		return (-1);
	if (ft_memcmp(path, "OLDPWD", 7) == 0)
		printf("%s\n", dest_path);
	free(dest_path);
	return (0);
}

int	exec_cd(char **cmd, t_list *env)
{
	char	*path;
	char	*dest_path;

	if (check_cmd_option(cmd) < 0)
		return (-1);
	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		error_exit("malloc failed", 0, 0, EXIT_FAILURE);
		return (-1);
	}
	if (cmd[1] == NULL)
		return (to_directory("HOME", path, cmd, env));
	else if (ft_memcmp("-", cmd[1], 2) == 0)
		return (to_directory("OLDPWD", path, cmd, env));
	else
	{
		dest_path = ft_strjoin_sep(path, cmd[1], "/");
		if (change_dir(dest_path, path, cmd[1], env) < 0)
			return (-1);
		free(dest_path);
	}
	free(path);
	return (0);
}
