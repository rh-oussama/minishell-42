/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 22:08:35 by oussama           #+#    #+#             */
/*   Updated: 2024/03/31 22:10:15 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_line_len(char *data)
{
	int	i;

	i = 0;
	while (data && data[i])
	{
		if (data && data[i] == '|' && is_operator(data, i))
			break ;
		i++;
	}
	return (i + 1);
}

char	*get_pipe_line(char *data, size_t *index)
{
	char	*line;
	int		i;

	i = 0;
	line = malloc(sizeof(char) * pipe_line_len(data));
	if (!line)
		return (NULL);
	*index += pipe_line_len(data) - 1;
	while (data && data[i])
	{
		if (data && data[i] == '|' && is_operator(data, i))
			break ;
		else
			line[i] = data[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

void	add_back(t_plist **head, t_plist *new)
{
	t_plist	*tmp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
}

t_plist	*create_plist(char *data)
{
	size_t	i;
	t_plist	*head;
	t_plist	*new;

	i = 0;
	head = NULL;
	while (i < ft_strlen(data))
	{
		new = new_node_plist(get_pipe_line(&data[i], &i));
		add_back(&head, new);
		i++;
	}
	return (head);
}

t_plist	*new_node_plist(char *data)
{
	t_plist	*new;

	new = malloc(sizeof(t_plist));
	if (!new)
		return (NULL);
	new->type = get_type_g(data);
	if (new->type == 'P')
		new->data = create_plist(data);
	else if (new->type == 'T')
		new->data = create_tree(data);
	else if (new->type == 'C')
		new->data = create_command(data);
	else
		new->data = ft_strdup(data);
	new->next = NULL;
	free(data);
	return (new);
}
