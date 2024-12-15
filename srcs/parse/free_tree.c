/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 22:08:26 by oussama           #+#    #+#             */
/*   Updated: 2024/03/30 22:08:27 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tree(t_aolist *tree);
void	free_pipe(t_plist *head);

void	free_command(t_cmd *tmp)
{
	void	*tmp2;

	while (tmp->in_red)
	{
		free(tmp->in_red->file);
		if (tmp->in_red->fd != -1)
			close(tmp->in_red->fd);
		tmp2 = tmp->in_red;
		tmp->in_red = tmp->in_red->next;
		free(tmp2);
	}
	while (tmp->out_red)
	{
		free(tmp->out_red->file);
		tmp2 = tmp->out_red;
		tmp->out_red = tmp->out_red->next;
		free(tmp2);
	}
	free_split(tmp->args);
	free(tmp);
}

void	free_pipe(t_plist *head)
{
	void	*tmp;

	while (head)
	{
		if (head->type == 'T')
			free_tree(head->data);
		else if (head->type == 'C')
			free_command(head->data);
		else if (head->type == 'O')
			free(head->data);
		else if (head->type == 'P')
			free_pipe(head->data);
		tmp = head;
		head = head->next;
		free(tmp);
	}
	free(head);
}

void	free_io(t_io *in, t_io *out)
{
	void	*tmp;

	while (in)
	{
		free(in->file);
		tmp = in;
		in = in->next;
		free(tmp);
	}
	while (out)
	{
		free(out->file);
		tmp = out;
		out = out->next;
		free(tmp);
	}
}

void	free_tree(t_aolist *tree)
{
	void	*tmp;

	free_io(tree->in, tree->out);
	while (tree)
	{
		if (tree->type == 'C')
			free_command(tree->data);
		else if (tree->type == 'P')
			free_pipe(tree->data);
		else if (tree->type == 'O')
			free(tree->data);
		else if (tree->type == 'T')
			free_tree(tree->data);
		tmp = tree;
		tree = tree->next;
		free(tmp);
	}
}
