/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 16:54:16 by sumilee           #+#    #+#             */
/*   Updated: 2024/03/12 21:07:25 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_exit(char *msg, char *cmd, char *arg, int code)
{
	if (code != 0 && msg != NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		if (cmd != NULL)
		{
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": ", 2);
		}
		if (arg != NULL)
		{
			ft_putstr_fd(arg, 2);
			ft_putstr_fd(": ", 2);
		}
		ft_putstr_fd(msg, 2);
		write(2, "\n", 1);
	}
	exit(code);
}

void	error_msg_only(char *msg, char *cmd, char *arg)
{
	if (msg != NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		if (cmd != NULL)
		{
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": ", 2);
		}
		if (arg != NULL)
		{
			ft_putstr_fd(arg, 2);
			ft_putstr_fd(": ", 2);
		}
		ft_putstr_fd(msg, 2);
		write(2, "\n", 1);
	}
}

void	*ft_malloc_err(size_t size)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)malloc(size);
	if (ptr == NULL)
		error_exit("malloc failed", 0, 0, EXIT_FAILURE);
	return ((void *)ptr);
}

static char	*ft_strcpy(char *dest, const char *src)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = 0;
	if (src != NULL)
		src_len = ft_strlen(src);
	while (dest != NULL && src != NULL && i < src_len + 1)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

char	*ft_strdup_err(const char *s1)
{
	char	*dest;

	dest = NULL;
	if (s1 != NULL)
		dest = (char *)ft_malloc_err(sizeof(char) * (ft_strlen(s1) + 1));
	ft_strcpy(dest, s1);
	return (dest);
}

char	*ft_strndup(char *origin, int count)
{
	char 	*str;
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
	return(str);
}
