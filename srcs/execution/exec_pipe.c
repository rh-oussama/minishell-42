/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 22:07:23 by oussama           #+#    #+#             */
/*   Updated: 2024/03/31 22:52:06 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_dup(int in, int *np)
{
	if (in != 0)
	{
		dup2(in, 0);
		close(in);
	}
	if (np[1] != 1)
	{
		close(np[0]);
		dup2(np[1], 1);
		close(np[1]);
	}
}

int	execute_pipe_helper(t_plist *head, int in, int *np)
{
	int	id;

	id = ft_fork();
	if (id == -1)
		return (-1);
	if (id == 0)
	{
		free(g_ptr.parse.arr);
		ft_dup(in, np);
		if (head->type == 'T')
			execute_tree(head->data);
		else if (head->type == 'C')
			execute_command(head->data, 0);
		else if (head->type == 'P')
			execute_pipe(head->data);
		exit(g_ptr.pstatus);
	}
	if (np)
	{
		close(np[1]);
		join_fd(&g_ptr.parse.arr, np[0]);
	}
	return (id);
}

void	ft_wait_pipe(int last_pid)
{
	int	status;
	int	pid;

	while (1)
	{
		pid = wait(&status);
		if (pid == -1)
			break ;
		if (WTERMSIG(g_ptr.pstatus) == 2 && pid == last_pid)
			g_ptr.pstatus = 130;
		else if (pid == last_pid)
			g_ptr.pstatus = WEXITSTATUS(status);
	}
}

void	ft_pipe(int *fd)
{
	if (pipe(fd) == -1)
		perror("pipe");
}

void	execute_pipe(t_plist *head)
{
	t_fdbackup	backup;
	int			fd[2];
	int			in;
	int			last_pid;

	fdbackup(&backup);
	g_ptr.parse.arr = malloc(sizeof(int) * 1);
	if (!g_ptr.parse.arr)
		return ;
	g_ptr.parse.arr[0] = -1;
	in = 0;
	while (head)
	{
		if (head->next)
			ft_pipe(fd);
		else
			fd[1] = 1;
		last_pid = execute_pipe_helper(head, in, fd);
		in = fd[0];
		head = head->next;
	}
	close_fd(g_ptr.parse.arr);
	ft_wait_pipe(last_pid);
	default_io(backup);
}
