/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_double_quots.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 22:07:27 by oussama           #+#    #+#             */
/*   Updated: 2024/04/02 01:25:57 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_double_quot_helper(char *str, char *new_str, int *index)
{
	char	*tmp;
	int		i;
	int		j;
	int		len;

	len = 1;
	while (str && str[len] && str[len] != '"')
		len++;
	tmp = ft_calloc(sizeof(char), (ft_strlen(new_str) + len + 3));
	i = 0;
	while (new_str && new_str[i])
	{
		tmp[i] = new_str[i];
		i++;
	}
	j = 1;
	while (str && str[j])
	{
		if (str && str[j] == '"')
			break ;
		tmp[i++] = str[j++];
		(*index)++;
	}
	tmp[i] = 0;
	return (tmp);
}

void	handle_double_quot(char **new_str, char *str, int *index)
{
	char	*tmp;
	int		i;
	char	*s;

	(*index) += 1;
	tmp = handle_double_quot_helper(str, *new_str, index);
	i = 0;
	s = malloc(sizeof(char) * (ft_strlen(str) + 3));
	if (!s)
		return ;
	s[0] = 0;
	while (tmp && tmp[i])
	{
		if (tmp && tmp[i] == '$' && i >= (int)ft_strlen(*new_str)
			&& (ft_isalnum(tmp[i + 1]) || tmp[i + 1] == '?' \
			|| str[i + 1] == '_'))
			handle_value(&s, &tmp[i], &i);
		else
			s = add_char_to_str(s, tmp[i]);
		i++;
	}
	free(*new_str);
	free(tmp);
	*new_str = s;
}
