/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exeution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 22:07:26 by oussama           #+#    #+#             */
/*   Updated: 2024/03/30 22:07:27 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_tree(t_aolist *tree);
void	execute_pipe(t_plist *head);
void	execute_command(t_cmd *cmd, int parent);

void	execution(void)
{
	void	*tmp;

	tmp = g_ptr.parse.aolist;
	if (g_ptr.parse.tmp_flag)
		return ;
	while (g_ptr.parse.aolist)
	{
		if (g_ptr.parse.aolist->type == 'C')
			execute_command(g_ptr.parse.aolist->data, 1);
		else if (g_ptr.parse.aolist->type == 'P')
			execute_pipe(g_ptr.parse.aolist->data);
		else if (g_ptr.parse.aolist->type == 'T')
			execute_tree(g_ptr.parse.aolist->data);
		else if (g_ptr.pstatus == 130)
			return ;
		else if (g_ptr.parse.aolist->type == 'O')
		{
			if ((g_ptr.pstatus == 0 && ft_strncmp(g_ptr.parse.aolist->data,
						"||", 2) == 0) || (g_ptr.pstatus != 0
					&& ft_strncmp(g_ptr.parse.aolist->data, "&&", 2) == 0))
				return ;
		}
		g_ptr.parse.aolist = g_ptr.parse.aolist->next;
	}
	g_ptr.parse.aolist = tmp;
}
