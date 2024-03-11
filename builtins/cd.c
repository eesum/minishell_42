/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 20:14:04 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/11 22:50:09 by sumilee          ###   ########.fr       */
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

void	to_oldpwd(char *current_path, char **cmd, t_list *env)
{
	char	*dest_path;

	dest_path = find_env("OLDPWD", env);
	if (dest_path == NULL)
		error_exit("OLDPWD not set", cmd[0], 0, 2);
	change_dir(dest_path, current_path, 0, env);
	printf("%s\n", dest_path);
	free(dest_path);
	return ;
}

void	to_home(char *current_path, char **cmd, t_list *env)
{
	char	*dest_path;

	dest_path = find_env("HOME", env);
	if (dest_path == NULL)
		error_exit("HOME not set", cmd[0], 0, 2);
	change_dir(dest_path, current_path, 0, env);
	printf("%s\n", dest_path);
	free(dest_path);
	return ;
}

void	exec_cd(char **cmd, t_list *env)
{
	char	*path;
	char	*dest_path;
	char	tmp[3];

	path = getcwd(NULL, 0);
	if (cmd[1] && cmd[1][0] == '-' && cmd[1][1] != '\0')
	{
		tmp[0] = '-';
		tmp[1] = cmd[1][1];
		tmp[2] = '\0';
		error_exit("invalid option", cmd[0], tmp, 2);
	}
	else if (cmd[1] && cmd[1][0] == '-' && cmd[1][1] == '\0')
		to_oldpwd(path, cmd, env);
	else if (cmd[1] == NULL || cmd[1][0] == '~' && cmd[1][1] == '\0')
		to_home(path, cmd, env);
	else
	{
		dest_path = ft_strjoin_sep(path, cmd[1], "/");
		change_dir(dest_path, path, cmd[1], env);
		free(dest_path);
	}
	free(path);
}

t_list *envp_to_lst(char **envp)
{
	t_list	*env;
	t_list	*new;
	int		i;

	i = 0;
	env = ft_malloc_err(sizeof(t_list));
	env->content = ft_strdup_err("?=0");
	env->next = NULL;
	while (envp[i])
	{
		new = ft_malloc_err(sizeof(t_list));
		new->content = ft_strdup_err(envp[i]);
		ft_lstadd_back(&env, new);
		i++;
	}
	return (env);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_execdata	data;
// 	t_list *cur;
	
// 	data.env = envp_to_lst(envp);
	
// 	char *cmd[3];

// 	cmd[0] = "cd";
// 	cmd[1] = NULL;
// 	// cmd[2] = NULL;
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
// 	while (1) {
// 		system("pwd");
// 		return 0;
// 	}
// 	return (0);
// }