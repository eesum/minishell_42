/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:03:20 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/19 15:26:59 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	export_no_arg(t_list *env)
{
	t_list	*cur;
	size_t	name_len;
	char	*name;
	int		i;

	cur = env;
	while (cur != NULL)
	{
		if (((char *)cur->content)[0] != '?')
		{
			printf("declare -x ");
			name_len = 0;
			while (((char *)cur->content)[name_len] != '=')
				name_len++;
			name = ft_substr((char *)cur->content, 0, name_len);
			if (name == NULL)
				return (-1);
			printf("%s=\"%s\"\n", name, &((char *)cur->content)[name_len + 1]);
			free(name);
		}
		cur = cur->next;
	}
	return (0);
}

int	exec_export(char **cmd, t_list *env)
{
	int		i;
	int		name_len;
	int		err_flag;
	char	*name;

	if (check_cmd_option(cmd) < 0)
		return (0);
	i = 0;
	err_flag = 0;
	if (cmd[1] == NULL)
		return (export_no_arg(env));
	while (cmd[++i])
	{
		name_len = check_valid_name(cmd[0], cmd[i], '=');
		if (name_len < 0)
		{
			err_flag = 1;
			continue ;
		}
		name = ft_substr_err(cmd[i], 0, name_len);
		update_env(name, &cmd[i][name_len + 1], env);
		free(name);
	}
	if (err_flag == 1)
		return (-1);
	return (0);
}
