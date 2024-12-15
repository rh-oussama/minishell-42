/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 22:07:24 by oussama           #+#    #+#             */
/*   Updated: 2024/03/30 22:07:25 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_tree_helper(t_aolist *tree)
{
	if (tree->type == 'C')
		execute_command(tree->data, 1);
	else if (tree->type == 'P')
		execute_pipe(tree->data);
	else if (tree->type == 'T')
		execute_tree(tree->data);
	else if (g_ptr.pstatus == 130)
		return (1);
	else if (tree->type == 'O')
	{
		if (g_ptr.pstatus == 0 && ft_strncmp(tree->data, "||", 2) == 0)
			return (1);
		if (g_ptr.pstatus != 0 && ft_strncmp(tree->data, "&&", 2) == 0)
			return (1);
	}
	return (0);
}

void	execute_tree(t_aolist *tree)
{
	int	pid;

	pid = ft_fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		g_ptr.pstatus = 0;
		if (apply_inredirections(tree->in) || apply_outredirections(tree->out))
			exit(1);
		if (g_ptr.pstatus)
			exit(g_ptr.pstatus);
		while (tree)
		{
			if (execute_tree_helper(tree))
				break ;
			tree = tree->next;
		}
		exit(g_ptr.pstatus);
	}
	if (wait(&g_ptr.pstatus) != -1 && WTERMSIG(g_ptr.pstatus) == 2)
		g_ptr.pstatus = 130;
	else
		g_ptr.pstatus = WEXITSTATUS(g_ptr.pstatus);
}
