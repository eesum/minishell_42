/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohyeki <seohyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:43:31 by seohyeki          #+#    #+#             */
/*   Updated: 2024/03/20 02:54:15 by seohyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_ispipe(char c)
{
	if (c == '|')
		return (1);
	return (0);
}

int	ft_isspace(char c)
{
	if (c == ' ' || (9 <= c && c <= 13))
		return (1);
	return (0);
}

int	ft_isredirect(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int	ft_isquote(char c)
{
	if (c == '\'')
		return (1);
	else if (c == '"')
		return (2);
	return (0);
}

int	check_token_type(char *str)
{
	if (*str == '<' && *(str + 1) == '<')
		return (TYPE_HEREDOC);
	else if (*str == '<' && *(str + 1) != '<')
		return (TYPE_INPUT);
	else if (*str == '>' && *(str + 1) != '>')
		return (TYPE_OUTPUT_T);
	else if (*str == '>' && *(str + 1) == '>')
		return (TYPE_OUTPUT_A);
	else if (ft_ispipe(*str))
		return (TYPE_PIPE);
	else
		return (TYPE_DEFAULT);
}

char	*ft_strndup(char *origin, int count)
{
	char	*str;
	size_t	i;
	char	c;

	str = (char *)ft_malloc_err(sizeof(char) + (count + 1));
	str[count] = '\0';
	i = 0;
	while (count)
	{
			str[i] = *origin;
			i++;
			origin++;
			count--;
	}
	return (str);
}
