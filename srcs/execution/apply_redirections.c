/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 22:07:19 by oussama           #+#    #+#             */
/*   Updated: 2024/04/01 00:02:08 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_open_error(char *str)
{
	perror(str);
	g_ptr.pstatus = 1;
}

int	open_inredirections(t_io *io)
{
	void	*tmp;

	tmp = io;
	while (io && io->file)
	{
		io->file = quot_value(io->file, 1);
		if (!io->file)
		{
			g_ptr.pstatus = ft_print_error("! ", "ambiguous redirect3\n", 1);
			return (1);
		}
		io->fd = open(io->file, O_RDONLY);
		if (io->fd == -1)
		{
			if (io->fd == -1)
				handle_open_error(io->file);
			io = tmp;
			return (1);
		}
		io = io->next;
	}
	io = tmp;
	return (0);
}

int	open_outredirections(t_io *io)
{
	void	*tmp;

	tmp = io;
	while (io)
	{
		io->file = quot_value(io->file, 1);
		if (!io->file)
		{
			g_ptr.pstatus = ft_print_error("! ", "ambiguous redirect4\n", 1);
			return (1);
		}
		if (io->type == 'O')
			io->fd = open(io->file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		else if (io->type == 'A')
			io->fd = open(io->file, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (io->fd == -1)
		{
			handle_open_error(io->file);
			io = tmp;
			return (1);
		}
		io = io->next;
	}
	io = tmp;
	return (0);
}
