/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 22:07:17 by oussama           #+#    #+#             */
/*   Updated: 2024/03/30 22:07:19 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_print_error(char *str, char *error, int n)
{
	int		len;
	char	*s;

	len = ft_strlen(str) + ft_strlen(error) + 15;
	s = ft_calloc(sizeof(char), len);
	ft_strlcat(s, "minishell: ", len);
	if (str)
	{
		ft_strlcat(s, str, len);
		ft_strlcat(s, ": ", len);
	}
	ft_strlcat(s, error, len);
	write(2, s, len);
	free(s);
	return (n);
}

int	apply_redirections(t_cmd *cmd)
{
	void	*in;
	void	*out;

	in = cmd->in_red;
	out = cmd->out_red;
	while (cmd->in_red)
	{
		dup2(cmd->in_red->fd, 0);
		close(cmd->in_red->fd);
		cmd->in_red = cmd->in_red->next;
	}
	while (cmd->out_red)
	{
		dup2(cmd->out_red->fd, 1);
		close(cmd->out_red->fd);
		cmd->out_red = cmd->out_red->next;
	}
	cmd->in_red = in;
	cmd->out_red = out;
	return (0);
}

int	apply_inredirections(t_io *io)
{
	while (io)
	{
		io->fd = open(io->file, O_RDONLY);
		if (io->fd == -1)
		{
			perror(io->file);
			g_ptr.pstatus = 1;
			return (1);
		}
		dup2(io->fd, 0);
		close(io->fd);
		io = io->next;
	}
	return (0);
}

int	apply_outredirections(t_io *io)
{
	char	*error;

	while (io)
	{
		if (io->type == 'O')
			io->fd = open(io->file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		else if (io->type == 'A')
			io->fd = open(io->file, O_WRONLY | O_APPEND, 0644);
		if (io->fd == -1)
		{
			error = malloc(sizeof(char) * (ft_strlen(io->file) + 12 + 1));
			if (!error)
				return (1);
			error[0] = 0;
			ft_strlcat(error, "minishell: ", 13);
			ft_strlcat(error, io->file, ft_strlen(io->file) + 13);
			perror(error);
			free(error);
			g_ptr.pstatus = 1;
			return (1);
		}
		dup2(io->fd, 1);
		io = io->next;
	}
	return (0);
}

void	default_io(t_fdbackup backup)
{
	dup2(backup.in, 0);
	close(backup.in);
	dup2(backup.out, 1);
	close(backup.out);
}
