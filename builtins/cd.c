/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 20:14:04 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/12 15:57:31 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_dir(char *dest_path, char *current_path, char *arg, t_list *env)
{
	if (chdir(dest_path) < 0)
	{
		if (errno == EACCES || errno == EFAULT)
			error_exit("Permission denied", "cd", arg, 2);
		else if (errno == ENOENT)
			error_exit("No such file or directory", "cd", arg, 2);
		else if (errno == ENOTDIR)
			error_exit("Not a directory", "cd", arg, 2);
		else
			error_exit("Error occured", "cd", arg, 2);
	}
	update_env("OLDPWD", current_path, env);
	update_env("PWD", dest_path, env);
}

void	to_directory(char *path, char *current_path, char **cmd, t_list *env)
{
	char	*dest_path;

	dest_path = find_env(path, env);
	if (dest_path == NULL)
		error_exit("not set", cmd[0], path, 2);
	change_dir(dest_path, current_path, 0, env);
	if (ft_memcmp(path, "OLDPWD", 7) == 0)
		printf("%s\n", dest_path);
	free(dest_path);
	return ;
}

void	exec_cd(char **cmd, t_list *env)
{
	char	*path;
	char	*dest_path;
	char	tmp[3];

	if (cmd[1] && cmd[1][0] == '-' && cmd[1][1] != '\0')
	{
		tmp[0] = '-';
		tmp[1] = cmd[1][1];
		tmp[2] = '\0';
		error_exit("invalid option", cmd[0], tmp, 2);
	}
	path = getcwd(NULL, 0);
	if (cmd[1] && cmd[1][0] == '-' && cmd[1][1] == '\0')
		to_directory("OLDPWD", path, cmd, env);
	else if (cmd[1] == NULL || cmd[1][0] == '~' && cmd[1][1] == '\0')
		to_directory("HOME", path, cmd, env);
	else
	{
		dest_path = ft_strjoin_sep(path, cmd[1], "/");
		change_dir(dest_path, path, cmd[1], env);
		free(dest_path);
	}
	free(path);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_execdata	data;
// 	t_list *cur;
	
// 	data.env = envp_to_lst(envp);
	
// 	char *cmd[3];

// 	cmd[0] = "cd";
// 	cmd[1] = "~";
// 	cmd[2] = NULL;
// 	cur = data.env;
// 	while (cur != NULL)
// 	{
// 		printf("%s\n", cur->content);
// 		cur = cur->next;
// 	}
// 	exec_cd(cmd, data.env);
	
// 	cur = data.env;
// 	while (cur != NULL)
// 	{
// 		printf("%s\n", cur->content);
// 		cur = cur->next;
// 	}
// 	return (0);
// }