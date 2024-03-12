/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 19:40:13 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/12 20:13:43 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_env(char *name, t_list *env)
{
	t_list	*cur;
	t_list	*tmp;
	int		name_len;

	cur = env;
	if (name == NULL)
		return ;
	name_len = ft_strlen(name);
	while (cur->next != NULL)
	{
		if (ft_memcmp((char *)cur->next->content, name, name_len) == 0)
		{
			tmp = cur->next;
			cur->next = cur->next->next;
			ft_lstdelone(tmp, free);
		}
		cur = cur->next;
	}
}

void	exec_unset(char **cmd, t_list *env)
{
	int		i;
	int		name_len;
	int		err_flag;
	char	*name;

	check_cmd_option(cmd);
	i = 0;
	err_flag = 0;
	while (cmd[++i])
	{
		name_len = check_valid_name(cmd[i], '\0');
		if (name_len < 0)
		{
			err_flag = 1;
			error_msg_only("not a valid identifier", cmd[0], cmd[i]);
			continue ;
		}
		name = ft_substr(cmd[i], 0, name_len);
		remove_env(name, env);
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
// 	exec_unset(&argv[1], data.env);
	
// 	cur = data.env;
// 	while (cur != NULL)
// 	{
// 		printf("%s\n", cur->content);
// 		cur = cur->next;
// 	}
// 	return (0);
// }