/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:33:41 by seohyeki          #+#    #+#             */
/*   Updated: 2024/03/26 01:23:02 by sumilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup(char *origin, int count)
{
	char	*str;
	size_t	i;

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
