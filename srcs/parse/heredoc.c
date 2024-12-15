/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 22:08:30 by oussama           #+#    #+#             */
/*   Updated: 2024/03/31 22:24:31 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_and_create_tmp_file(char *limiter, int flag)
{
	char	*tmp;
	char	*buffer;
	char	*new_buffer;

	buffer = NULL;
	while (1)
	{
		tmp = readline(">");
		if (!tmp)
			break ;
		if (ft_strncmp(tmp, limiter, ft_strlen(limiter) + 1) == 0)
		{
			free(tmp);
			break ;
		}
		tmp = ft_add_nl(tmp);
		new_buffer = ft_strjoin_g(buffer, tmp);
		free(buffer);
		buffer = new_buffer;
		free(tmp);
	}
	return (create_tempfile(buffer, flag));
}

char	*read_heredoc(char *limiter, int quots)
{
	int		pid;
	int		flag;
	char	*pf[2];

	g_ptr.parse.herdoc_flag = 1;
	pid = ft_fork();
	if (pid == -1)
		return (NULL);
	if (pid == 0)
	{
		flag = read_and_create_tmp_file(limiter, quots);
		exit(flag);
	}
	waitpid(pid, &flag, 0);
	g_ptr.parse.herdoc_flag = 0;
	if (WTERMSIG(flag) || WEXITSTATUS(flag) == 255)
	{
		g_ptr.parse.tmp_flag = 1;
		return (NULL);
	}
	else
		pf[0] = ft_itoa(WEXITSTATUS(flag));
	pf[1] = ft_strjoin("/tmp/minishell_temprary_buffer_", pf[0]);
	free_args_list(pf[0], limiter, NULL, NULL);
	return (pf[1]);
}

char	*generate_a_buffer_name(int flag)
{
	char	*name;
	char	*str;

	str = ft_itoa(flag);
	name = ft_strjoin("/tmp/minishell_temprary_buffer_", str);
	free(str);
	return (name);
}

int	generate_flag(void)
{
	char	*name;
	char	*str;
	int		i;

	i = 0;
	while (1)
	{
		str = ft_itoa(i);
		name = ft_strjoin("/tmp/minishell_temprary_buffer_", str);
		if (access(name, F_OK) != 0)
		{
			free(name);
			free(str);
			return (i);
		}
		i++;
		free(name);
		free(str);
	}
	return (-1);
}

int	create_tempfile(char *buffer, int quots)
{
	char	*file_name;
	int		flag;
	int		fd;

	flag = generate_flag();
	file_name = generate_a_buffer_name(flag);
	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0400);
	if (fd == -1)
	{
		perror("heredoc");
		free(file_name);
		free(buffer);
		return (-1);
	}
	if (!quots)
		buffer = quot_value(buffer, 1);
	if (write(fd, buffer, ft_strlen(buffer)) == -1)
		perror("write in pipe");
	close(fd);
	free(buffer);
	free(file_name);
	return (flag);
}
