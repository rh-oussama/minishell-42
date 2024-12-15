/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 22:08:48 by oussama           #+#    #+#             */
/*   Updated: 2024/03/31 22:25:42 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_a_pipe(char *data)
{
	int	i;

	i = 0;
	while (data && data[i])
	{
		if (data && data[i] == '|' && data[i + 1] != '|')
		{
			if (is_operator(data, i))
				return (1);
		}
		i++;
	}
	return (0);
}

int	is_a_parenthesis(char *data)
{
	int	i;

	i = 0;
	while (data && data[i] && ft_isspace(data[i]))
		i++;
	if (data && data[i] == '(')
		return (1);
	return (0);
}

char	get_type_g(char *data)
{
	int	i;

	i = 0;
	while (data && data[i] && ft_isspace(data[i]))
		i++;
	if (data && (ft_strncmp("&&", &data[i], 2) == 0 || ft_strncmp("||",
				&data[i], 2) == 0))
		return ('O');
	else if (data && is_a_pipe(&data[i]))
		return ('P');
	else if (data && is_a_parenthesis(&data[i]))
		return ('T');
	else
		return ('C');
}
