/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:03:20 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/23 17:45:08 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"
#include "../include/exec.h"
#include <stdio.h>

static char	*ft_substr_err(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	i;
	size_t			s_len;

	i = 0;
	s_len = ft_strlen(s);
	if (s_len <= start)
		len = 0;
	else if (s_len < start + len)
		len = s_len - start;
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (sub == NULL)
		error_exit("malloc failed", 0, 0, EXIT_FAILURE);
	while (i < len && s[start + i])
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

static int	export_no_arg(t_list *env)
{
	t_list	*cur;
	size_t	name_len;
	char	*name;

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

static void	export_with_arg(char **cmd, t_list *env, int *err_flag)
{
	int		i;
	int		name_len;
	char	*name;

	i = 1;
	while (cmd[i])
	{
		name_len = check_valid_name(cmd[0], cmd[i], '=');
		if (name_len < 0)
		{
			*err_flag = 1;
			i++;
			continue ;
		}
		name = ft_substr_err(cmd[i], 0, name_len);
		update_env(name, &cmd[i][name_len + 1], env);
		free(name);
		i++;
	}
}

int	exec_export(char **cmd, t_list *env)
{
	int		err_flag;

	if (check_cmd_option(cmd) < 0)
		return (-1);
	err_flag = 0;
	if (cmd[1] == NULL)
		return (export_no_arg(env));
	else
		export_with_arg(cmd, env, &err_flag);
	if (err_flag == 1)
		return (-1);
	return (0);
}
