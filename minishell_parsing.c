/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohyeki <seohyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 17:23:20 by seohyeki          #+#    #+#             */
/*   Updated: 2024/03/09 19:59:17 by seohyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_type(char *str)
{
	//strncmp쓰는게 나으려나?
	if (*str == 34) //""
		return (1);
	else if (*str == 39) //''
		return (2);
	else if (*str == '|' && *(str + 1) == '\0') //pipe
		return (3);
	else if (*str == '<' && *(str + 1) != '<') // <
		return (4);
	else if (*str == '>' && *(str + 1) == '>') // >
		return (5);
	else if (*str == '<' && *(str + 1) == '<') // <<
		return (6);
	else if (*str == '>' && *(str + 1) == '>') // >>
		return (7);
	else
	 	return (0);
}

void	count_quote(char *str, int *i, int *cnt)
{
	char	c;
	
	c = str[(*i)];
	(*i)++;
	(*cnt)++;
	while (str[*i] != c && str[*i])
	{
		(*i)++;
		(*cnt)++;
	}
	if (str[*i] != '\0')
	{
		(*i)++;
		(*cnt)++;
	}
}

void	make_token(t_token **head, char *str, int *i, int *cnt)
{
	int		type;
	char	*token;

	while (str[*i] == 34 || str[*i] == 39)
		count_quote(str, i, cnt);
	token = ft_strndup(str + *i - *cnt, *cnt);
	type = check_type(token);
	ft_lstadd_back(head, ft_make_newtoken(token, type));
	(*cnt) = -1;
}

void	parsing(char *str, t_token **head)
{
	int		i;
	int		cnt;

	i = 0;
	cnt = 0;
	while (str[i])
	{
		if (str[i] == 32) //공백(스페이스만 취급하는데 탭같은거도 처리해야하나?)
		{
			if (cnt != 0)
				make_token(head, str, &i, &cnt);
			cnt = -1;
		}
		else if (str[i] == '\'' || str[i] == '"') //쌍따옴표
		{
			if (cnt == 0)
			 	make_token(head, str, &i, &cnt);
		}
		i++;
		cnt++;
	}
	if (cnt != 0)
		make_token(head, str, &i, &cnt);
}
