/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:03:20 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/12 18:43:33 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_valid_name(char *arg)
{
	int	i;

	if (arg && arg[0] != 95 && \
		(arg[0] < 65 || (arg[0] > 90 && arg[0] < 97) || arg[0] > 122))
		return (-1);
	i = 1;
	while (arg && arg[i] && arg[i] != '=')
	{
		if (arg[i] != 95 && \
			(arg[i] < 48 || (arg[i] > 57 && arg[i] < 65) || \
			(arg[i] > 90 && arg[i] < 97) || arg[i] > 122))
			return (-1);
		i++;
	}
	return (i);
}

void	export_no_arg(t_list *env)
{
	t_list	*cur;
	size_t	name_len;
	char	*name;
	int		i;

	cur = env;
	while (cur != NULL)
	{
		printf("declare -x ");
		name_len = 0;
		while (((char *)cur->content)[name_len] != '=')
			name_len++;
		name = ft_substr((char *)cur->content, 0, name_len);
		printf("%s=\"%s\"\n", name, &((char *)cur->content)[name_len + 1]);
		free(name);
		cur = cur->next;
	}
}

void	exec_export(char **cmd, t_list *env)
{
	int	i;
	int	name_len;
	int	err_flag;
	char	*name;

	check_cmd_option(cmd);
	i = 0;
	err_flag = 0;
	if (cmd[1] == NULL)
		export_no_arg(env);
	while (cmd[++i])
	{
		name_len = check_valid_name(cmd[i]);
		if (name_len < 0)
		{
			err_flag = 1;
			error_msg_only("not a valid identifier", cmd[0], cmd[i]);
			continue ;
		}
		name = ft_substr(cmd[i], 0, name_len);
		update_env(name, &cmd[i][name_len + 1], env);
		free(name);
	}
	if (err_flag == 1)
		exit(EXIT_FAILURE);
}

// t_list *envp_to_lst(char **envp)
// {
// 	t_list	*env;
// 	t_list	*new;
// 	int		i;

// 	i = 0;
// 	env = ft_lstnew(ft_strdup_err("?=0"));
// 	if (env == NULL)
// 		error_exit("malloc failed", 0, 0, EXIT_FAILURE);
// 	while (envp && envp[i])
// 	{
// 		new = ft_lstnew(ft_strdup_err(envp[i]));
// 		if (env == NULL)
// 			error_exit("malloc failed", 0, 0, EXIT_FAILURE);
// 		ft_lstadd_back(&env, new);
// 		i++;
// 	}
// 	return (env);
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	t_execdata	data;
// 	t_list *cur;
	
// 	data.env = envp_to_lst(envp);

// 	cur = data.env;
// 	while (cur != NULL)
// 	{
// 		printf("%s\n", cur->content);
// 		cur = cur->next;
// 	}
// 	exec_export(&argv[1], data.env);
	
// 	cur = data.env;
// 	while (cur != NULL)
// 	{
// 		printf("%s\n", cur->content);
// 		cur = cur->next;
// 	}
// 	return (0);
// }