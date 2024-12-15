/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 22:08:39 by oussama           #+#    #+#             */
/*   Updated: 2024/03/31 22:10:38 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	close_pair(char *str, int i)
{
	int	open;
	int	close;

	open = 0;
	close = 0;
	while (str && str[i])
	{
		if (str && str[i] == '(')
			open++;
		else if (str && str[i] == ')')
			close++;
		if (open == close)
			return (i);
		i++;
	}
	return (-1);
}

char	*remove_parenthesis(char *row_data)
{
	char	*data;
	int		i;

	i = 0;
	while (row_data && row_data[i] && ft_isspace(row_data[i]))
		i++;
	data = ft_strndup(&row_data[i + 1], close_pair(row_data, i) - i - 1);
	return (data);
}

t_aolist	*last_node_aolist(t_aolist *head)
{
	t_aolist	*tmp;

	tmp = head;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	split_and_or_helper(char *row_data, char **data, int *i, int *u)
{
	if (ft_strncmp("&&", &row_data[*i], 2) == 0 && is_operator(row_data, *i))
	{
		data[(*u)++] = ft_strdup("&&");
		(*i)++;
	}
	else if (ft_strncmp("||", &row_data[*i], 2) == 0 && is_operator(row_data,
			*i))
	{
		data[(*u)++] = ft_strdup("||");
		(*i)++;
	}
	else
		data[(*u)++] = get_split_line(&row_data[*i], i);
}
