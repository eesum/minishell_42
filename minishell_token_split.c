/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_token_split.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohyeki <seohyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 17:23:20 by seohyeki          #+#    #+#             */
/*   Updated: 2024/03/14 16:34:09 by seohyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_type(char *str)
{
	if (*str == '<' && *(str + 1) == '<')
		return (1);
	else if (*str == '<' && *(str + 1) != '<')
		return (2);
	else if (*str == '>' && *(str + 1) != '>')
		return (3);
	else if (*str == '>' && *(str + 1) == '>')
		return (4);
	else if (ft_ispipe(*str))
		return (5);
	else
	 	return (0);
}

static void	make_token(t_list **head, char *str, int *i, int *cnt)
{
	int		type;
	char	*token_str;
	t_token	*token;

	if (*cnt == 0)
		return;
	type = check_type(str + *i - *cnt);
	token_str = ft_strndup(str + *i - *cnt, *cnt);
	token = (t_token *)ft_malloc_err(sizeof(t_token));
	token->str = token_str;
	token->type = type;
	ft_lstadd_back(head, ft_lstnew(token));
	(*cnt) = 0;
}

static void	make_pipe_redirect_token(t_list **head, char *str, int *i, int *cnt)
{
	char	c;
	
	make_token(head, str, i, cnt);
	(*cnt)++;
	if (ft_ispipe(str[*i]))
	{
		(*i)++;
		if (ft_ispipe(str[*i]) || str[*i] == '\0')
			error_exit ("syntax error", 0, 0, 1);
	}
	else if (ft_isredirect(str[*i]))
	{
		c = str[*i];
		(*i)++;
		if (str[*i] == c)
		{
			(*i)++;
			(*cnt)++;
			if (ft_ispipe(str[*i]) || ft_isredirect(str[*i]) || str[*i] == '\0')
				error_exit ("syntax error", 0, 0, 1);
		}
		else if (ft_ispipe(str[*i]) || ft_isredirect(str[*i]) || str[*i] == '\0')
			error_exit ("syntax error", 0, 0, 1);
	}
	make_token(head, str, i, cnt);
}
	

static void	count_quote(char *str, int *i, int *cnt)
{
	char	c;
	
	while (ft_isquote(str[*i]))
	{
		c = str[(*i)];
		(*i)++;
		(*cnt)++;
		while (str[*i] != c && str[*i])
		{
			(*i)++;
			(*cnt)++;
		}
		if (str[*i] == '\0')
			error_exit ("syntax error", 0, 0, 1);
		else
		{
			(*i)++;
			(*cnt)++;
		}
	}
}

void	split_token(t_list **head, char *str)
{
	int		i;
	int		cnt;

	i = 0;
	cnt = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]))
		{
			make_token(head, str, &i, &cnt);
			i++;
		}
		else if (ft_ispipe(str[i]) || ft_isredirect(str[i]))
			make_pipe_redirect_token(head, str, &i, &cnt);
		else if (str[i] == '\'' || str[i] == '"')
			count_quote(str, &i, &cnt);
		else
		{
			i++;
			cnt++;
		}
	}
	make_token(head, str, &i, &cnt);
}
