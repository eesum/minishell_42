/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohyeki <seohyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:28:14 by seohyeki          #+#    #+#             */
/*   Updated: 2024/03/23 15:40:08 by seohyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# define SYNTAX_ERROR 1

# include "minishell.h"

char	*get_env_name(char *str);
void	count_total_len(char *str, t_list *env, size_t *len);
void	change_default(t_parsedata *data, size_t *i, size_t *j, t_list *env);
void	change_quote(t_parsedata *data, size_t *i, size_t *j, t_list *env);
void	parsing_env(t_parsedata *data, t_list *env);
int		split_token(t_list **head, char *str);
int		check_token_type(char *str);
void	delete_quote(t_list **head);
int		beautify_token(t_list **head, t_list **pipe);
int		parsing(t_parsedata *parse, t_execdata *exec);

/*parse utils*/
int		ft_ispipe(char c);
int		ft_isredi(char c);
int		ft_isquote(char c);
char	*ft_strndup(char *origin, int count);

#endif