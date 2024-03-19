/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_token_split.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohyeki <seohyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 17:23:20 by seohyeki          #+#    #+#             */
/*   Updated: 2024/03/19 18:02:26 by seohyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	make_token(t_list **head, char *str, int *i, int *cnt)
{
	int		type;
	char	*token_str;
	t_token	*token;

	if (*cnt == 0)
		return ;
	type = check_token_type(str + *i - *cnt);
	token_str = ft_strndup(str + *i - *cnt, *cnt);
	token = (t_token *)ft_malloc_err(sizeof(t_token));
	token->str = token_str;
	token->type = type;
	ft_lstadd_back(head, ft_lstnew(token));
	(*cnt) = 0;
}

static int	make_pipe_redirect_token(t_list **head, char *str, int *i, int *cnt)
{
	char	c;

	make_token(head, str, i, cnt);
	(*cnt)++;
	if (ft_ispipe(str[*i]))
	{
		(*i)++;
		if (ft_ispipe(str[*i]) || !str[*i])
			return (1);
	}
	else if (ft_isredirect(str[*i]))
	{
		c = str[(*i)++];
		if (str[*i] == c)
		{
			(*i)++;
			(*cnt)++;
			if (ft_ispipe(str[*i]) || ft_isredirect(str[*i]) || !str[*i])
				return (SYNTAX_ERROR);
		}
		else if (ft_ispipe(str[*i]) || ft_isredirect(str[*i]) || !str[*i])
			return (SYNTAX_ERROR);
	}
	make_token(head, str, i, cnt);
	return (0);
}

static int	count_quote(char *str, int *i, int *cnt)
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
			return (SYNTAX_ERROR);
		else
		{
			(*i)++;
			(*cnt)++;
		}
	}
	return (0);
}

static int	split_loop(t_list **head, char *str, int *i, int *cnt)
{
	if (ft_ispipe(str[*i]) || ft_isredirect(str[*i]))
	{
		if (make_pipe_redirect_token(head, str, i, cnt))
		{
			ft_tokenlst_free(head);
			return (SYNTAX_ERROR);
		}
	}	
	else if (ft_isquote(str[*i]))
	{
		if (count_quote(str, i, cnt))
		{
			ft_tokenlst_free(head);
			return (SYNTAX_ERROR);
		}
	}
	return (0);
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
		else if (ft_isquote(str[i]) || ft_ispipe(str[i])
			|| ft_isredirect(str[i]))
		{
			if (split_loop(head, str, &i, &cnt))
				return ;
		}
		else
		{
			i++;
			cnt++;
		}
	}
	make_token(head, str, &i, &cnt);
}
