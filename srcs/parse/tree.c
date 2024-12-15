/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 22:08:46 by oussama           #+#    #+#             */
/*   Updated: 2024/03/31 22:11:28 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_io_in_parenthese(char *row_data, t_io **in, t_io **out)
{
	int		i;
	char	**data;

	i = ft_strlen(row_data) - 1;
	while (i >= 0 && row_data[i] != ')')
		i--;
	i++;
	data = ft_split_own(&row_data[i]);
	if (!data)
		return ;
	*out = fill_outred(data);
	*in = fill_inred(data);
	free_split(data);
}

t_aolist	*create_tree_helper(char **data, t_io *in, t_io *out)
{
	t_aolist	*head;
	t_aolist	*node;
	t_aolist	*last;
	int			i;

	i = 0;
	head = NULL;
	while (data && data[i])
	{
		last = last_node_aolist(head);
		node = new_node_aolist(data[i], last);
		node->in = in;
		node->out = out;
		if (!head)
			head = node;
		else
			last->next = node;
		i++;
	}
	return (head);
}

t_aolist	*create_tree(char *row_data)
{
	t_aolist	*head;
	t_io		*in;
	t_io		*out;
	char		**data;

	out = NULL;
	in = NULL;
	fill_io_in_parenthese(row_data, &in, &out);
	row_data = remove_parenthesis(row_data);
	data = split_and_or(row_data);
	head = create_tree_helper(data, in, out);
	free_split(data);
	free(row_data);
	return (head);
}

t_aolist	*new_node_aolist(char *data, t_aolist *prev)
{
	t_aolist	*new;

	new = malloc(sizeof(t_aolist));
	if (!new)
		return (NULL);
	new->type = get_type_g(data);
	new->next = NULL;
	new->prev = prev;
	new->in = NULL;
	new->out = NULL;
	if (new->type == 'P')
		new->data = create_plist(data);
	else if (new->type == 'T')
		new->data = create_tree(data);
	else if (new->type == 'C')
		new->data = create_command(data);
	else
		new->data = ft_strdup(data);
	return (new);
}
