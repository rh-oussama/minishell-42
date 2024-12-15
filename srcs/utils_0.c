/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 22:07:13 by oussama           #+#    #+#             */
/*   Updated: 2024/03/30 22:07:14 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fdbackup(t_fdbackup *backup)
{
	backup->in = dup(0);
	backup->out = dup(1);
	if (backup->in == -1 || backup->out == -1)
		perror("dup");
}

void	clean_all(void)
{
	free_split(g_ptr.envp);
}

void	clean(void)
{
	int		i;
	char	*name;
	char	*str;

	if (g_ptr.parse.tmp_flag)
		return ;
	free_split(g_ptr.parse.data);
	free_tree(g_ptr.parse.aolist);
	i = 0;
	while (1)
	{
		str = ft_itoa(i);
		name = ft_strjoin("/tmp/minishell_temprary_buffer_", str);
		free(str);
		if (access(name, F_OK) == 0)
			unlink(name);
		else
		{
			free(name);
			break ;
		}
		free(name);
		i++;
	}
	return ;
}

void	check_shlvl_cwd(void)
{
	int		i;
	int		shlvl;
	int		pwd;
	char	*cwd;

	shlvl = 0;
	pwd = 0;
	i = 0;
	while (g_ptr.envp && g_ptr.envp[i])
	{
		if (ft_strncmp(g_ptr.envp[i], "SHLVL=", 6) == 0)
			shlvl = 1;
		if (ft_strncmp(g_ptr.envp[i], "PWD=", 4) == 0)
			pwd = 1;
		i++;
	}
	if (shlvl == 0)
		add_it_on_env("SHLVL", "1");
	if (pwd == 0)
	{
		cwd = ft_getpwd();
		add_it_on_env("PWD", cwd);
		free(cwd);
	}
	add_it_on_env("_", "minishell");
}

void	init_ptr(char **envp)
{
	signal(SIGINT, sigint_handle);
	signal(SIGQUIT, SIG_IGN);
	g_ptr.envp = envp_dup(envp);
	check_shlvl_cwd();
}
