/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:51:51 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/15 13:04:58 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_env(char **cmd, t_list *env)
{
	int	i;
	int	name_len;
	char	*name;
	t_list	*cur;

	check_cmd_option(cmd);
	i = 0;
	if (cmd[1] != NULL)
	{
		error_msg_only("not a valid argument", cmd[0], cmd[i]);
		return (-1);
	}
	cur = env;
	while (cur != NULL)
	{
		if (((char *)cur->content)[0] != '?')
			printf("%s\n", ((char *)cur->content));
		cur = cur->next;
	}
	return (0);
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
// 	exec_env(&argv[1], data.env);
	
// 	cur = data.env;
// 	while (cur != NULL)
// 	{
// 		printf("%s\n", cur->content);
// 		cur = cur->next;
// 	}
// 	return (0);
// }