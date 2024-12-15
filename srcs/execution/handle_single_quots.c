/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_single_quots.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 22:07:29 by oussama           #+#    #+#             */
/*   Updated: 2024/03/31 22:50:37 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*single_quot_buffer(char *str, char *new_str)
{
	int		len;
	char	*buff;

	len = 0;
	while (str && str[len] && str[len + 1] != '\'')
		len++;
	buff = malloc(sizeof(char) * (ft_strlen(new_str) + len + 2));
	return (buff);
}

void	handle_single_quot(char **new_str, char *str, int *index)
{
	char	*tmp;
	int		i;
	int		j;

	(*index) += 1;
	tmp = single_quot_buffer(str, *new_str);
	if (!tmp)
		return ;
	i = -1;
	while ((*new_str) && (*new_str)[++i])
		tmp[i] = (*new_str)[i];
	j = 1;
	while (str && str[j])
	{
		if (str && str[j] == '\'')
			break ;
		tmp[i++] = str[j++];
		(*index)++;
	}
	tmp[i] = 0;
	free(*new_str);
	*new_str = tmp;
}
