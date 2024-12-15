/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 22:07:14 by oussama           #+#    #+#             */
/*   Updated: 2024/03/31 22:22:11 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**envp_dup(char **envp)
{
	int		i;
	char	**new_envp;
	char	*tmp;

	i = 0;
	while (envp && envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 1));
	if (!new_envp || !envp)
		return (NULL);
	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], "SHLVL=", 6) == 0)
		{
			tmp = ft_itoa(ft_atoi(&envp[i][6]) + 1);
			new_envp[i] = ft_strjoin("SHLVL=", tmp);
			free(tmp);
		}
		else
			new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

int	is_file(char *path)
{
	struct stat	info;

	if (stat(path, &info) == 0)
	{
		if (S_ISREG(info.st_mode))
			return (1);
	}
	return (0);
}

int	is_directory(char *path)
{
	struct stat	info;

	if (stat(path, &info) == 0)
	{
		if (S_ISDIR(info.st_mode))
			return (1);
	}
	return (0);
}

void	check_file(char *command)
{
	if (!command)
		return ;
	if ((command[0] == '.' || command[1] == '/') && is_file(command))
		g_ptr.pstatus = ft_print_error(command, "Permission denied\n", 126);
	else if ((command[0] == '.' || command[1] == '/') && is_directory(command))
		g_ptr.pstatus = ft_print_error(command, "is directory\n", 126);
	else if (command[0] == '.' || command[1] == '/')
		g_ptr.pstatus = ft_print_error(command, "No such file or directory\n",
				127);
	else if (is_directory(command))
		g_ptr.pstatus = ft_print_error(command, "is directory\n", 126);
	else
		g_ptr.pstatus = ft_print_error(command, "command not found\n", 127);
}

char	*get_final_path(char *command)
{
	char	**path;
	int		i;
	char	*full_path;
	char	*tmp;

	i = 0;
	if (access(command, F_OK) == 0 && ft_strchr(command, '/'))
		return (ft_strdup(command));
	path = get_path(g_ptr.envp);
	i = 0;
	while (command && command[0] && command[0] != '/' && command[0] != '.'
		&& path && path[i] != NULL)
	{
		tmp = ft_strjoin(path[i], "/");
		full_path = ft_strjoin(tmp, command);
		free(tmp);
		if (access(full_path, F_OK) == 0 && access(full_path, X_OK) == 0)
			return (free_split(path), full_path);
		free(full_path);
		i++;
	}
	return (free_split(path), NULL);
}
