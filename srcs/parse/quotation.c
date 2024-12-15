/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 22:08:36 by oussama           #+#    #+#             */
/*   Updated: 2024/03/31 21:50:30 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quotation_helper(char *s, int *u, char *str, int *i)
{
	int	j;

	j = 0;
	j = skip_quotes_i(str, i) - 1;
	while (j > 1)
	{
		s[(*u)++] = str[*i - j];
		j--;
	}
	return (s);
}

char	*remove_quotation(char *str)
{
	char	*s;
	int		i;
	int		u;

	i = 0;
	u = 0;
	s = malloc(sizeof(char) * (ft_strlen(str) + 3));
	if (!s)
		return (NULL);
	while (str && str[i])
	{
		if (str && (str[i] == '"' || str[i] == '\''))
		{
			remove_quotation_helper(s, &u, str, &i);
		}
		else
			while (str && (str[i] && !(str[i] == '"' || str[i] == '\'')))
				s[u++] = str[i++];
	}
	s[u] = 0;
	return (s);
}

int	skip_quotation(char *data, int index)
{
	int	i;
	int	sq;
	int	dq;

	sq = 0;
	dq = 0;
	i = index;
	while (data && data[i] && ft_isspace(data[i]))
		i++;
	if (data && data[i] == '"')
		dq++;
	else if (data && data[i] == '\'')
		sq++;
	else
		return (i);
	i++;
	while (data && data[i])
	{
		if (data && data[i] == '"' && dq)
			return (i + 0);
		else if (data && data[i] == '\'' && sq)
			return (i + 0);
		i++;
	}
	return (i);
}
