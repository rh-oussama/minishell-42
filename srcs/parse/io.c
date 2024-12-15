/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 22:08:32 by oussama           #+#    #+#             */
/*   Updated: 2024/03/30 22:08:33 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_io	*new_io_node(char *data, char type)
{
	t_io	*new;

	new = malloc(sizeof(t_io));
	if (!new)
		return (NULL);
	new->type = type;
	new->file = data;
	new->next = NULL;
	return (new);
}

void	add_back_io(t_io **head, t_io *new)
{
	t_io	*tmp;

	if (!new)
		return ;
	if (!(*head))
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp && tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
}
