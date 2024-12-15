/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 22:07:33 by oussama           #+#    #+#             */
/*   Updated: 2024/03/30 22:07:34 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path(char **envp)
{
	while (envp && *envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			return (ft_split(*envp + 5, ':'));
		envp++;
	}
	return (NULL);
}

void	join_fd(int **fd_arr, int fd)
{
	int	i;
	int	j;
	int	*arr;

	i = 0;
	j = 0;
	while ((*fd_arr)[i] != -1)
		i++;
	arr = (int *)malloc(sizeof(int) * (i + 2));
	if (!arr)
		return ;
	while (j < i)
	{
		arr[j] = (*fd_arr)[j];
		j++;
	}
	arr[j++] = fd;
	arr[j] = -1;
	free(*fd_arr);
	*fd_arr = arr;
}

void	close_fd(int *fd_arr)
{
	int	i;

	i = 0;
	while (fd_arr[i] != -1)
	{
		if (fd_arr[i] != 0 && fd_arr[i] != 1 && fd_arr[i] != 2)
			close(fd_arr[i]);
		i++;
	}
	free(fd_arr);
	g_ptr.parse.arr = NULL;
}

int	ft_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		signal(SIGINT, SIG_DFL);
	return (pid);
}
