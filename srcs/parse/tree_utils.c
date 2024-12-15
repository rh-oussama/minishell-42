/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 22:08:41 by oussama           #+#    #+#             */
/*   Updated: 2024/03/31 22:11:17 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_and_or(char *row_data)
{
	char	**data;
	int		i;
	int		u;

	u = 0;
	data = malloc(sizeof(char *) * split_and_or_len(row_data));
	if (!data)
		return (NULL);
	i = -1;
	while (row_data && row_data[++i])
		split_and_or_helper(row_data, data, &i, &u);
	data[u] = NULL;
	return (data);
}

char	*get_split_line(char *row_data, int *index)
{
	int		i;
	int		j;
	char	*split;

	j = 0;
	split = malloc(sizeof(char) * split_line_len(row_data));
	if (!split)
		return (NULL);
	(*index)--;
	i = -1;
	while (row_data && row_data[++i])
	{
		if ((ft_strncmp(&row_data[i], "&&", 2) == 0 || ft_strncmp(&row_data[i],
					"||", 2) == 0) && is_operator(row_data, i))
			break ;
		else
			split[j++] = row_data[i];
		(*index)++;
	}
	split[j] = 0;
	return (split);
}

int	split_line_len(char *row_data)
{
	int	i;

	i = -1;
	while (row_data && row_data[++i])
		if ((ft_strncmp(&row_data[i], "&&", 2) == 0 || ft_strncmp(&row_data[i],
					"||", 2) == 0) && is_operator(row_data, i))
			break ;
	return (i + 1);
}

int	split_and_or_len(char *row_data)
{
	int	i;
	int	len;

	len = 1;
	i = -1;
	while (row_data && row_data[++i])
	{
		if ((ft_strncmp(&row_data[i], "&&", 2) == 0 || ft_strncmp(&row_data[i],
					"||", 2) == 0) && is_operator(row_data, i))
		{
			len += 2;
			i++;
		}
	}
	return (len + 1);
}

void	create_aolist(void)
{
	t_aolist	*head;
	t_aolist	*node;
	t_aolist	*last;
	int			i;

	i = 0;
	head = NULL;
	while (g_ptr.parse.data[i])
	{
		last = last_node_aolist(head);
		node = new_node_aolist(g_ptr.parse.data[i], last);
		if (!head)
			head = node;
		else
			last->next = node;
		i++;
	}
	g_ptr.parse.aolist = head;
}
