/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bic_cd_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:42:43 by orhaddao          #+#    #+#             */
/*   Updated: 2024/04/02 01:26:26 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_handle_home(t_env tmp_env, char *oldpwd)
{
	if (tmp_env.value == NULL)
	{
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		g_ptr.pstatus = 1;
		return ;
	}
	if (chdir(tmp_env.value) == -1)
	{
		perror("minishell: cd: ");
		g_ptr.pstatus = 1;
		return ;
	}
	else
	{
		update_curent_pwd();
		update_cwd(oldpwd);
		g_ptr.pstatus = 0;
	}
}

void	cd_handle_path(char **cmd, char *oldpwd)
{
	if (chdir(cmd[1]) == -1)
	{
		perror("minishell: cd: ");
		g_ptr.pstatus = 1;
		return ;
	}
	else
	{
		update_curent_pwd();
		update_cwd(oldpwd);
		g_ptr.pstatus = 0;
	}
}

void	free_args_list(void *sa, void *sb, char *sc, char *sd)
{
	if (sa)
		free(sa);
	if (sb)
		free(sb);
	if (sc)
		free(sc);
	if (sd)
		free(sd);
}

char	*ft_getpwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_print_error("getcwd", "error in current working directory you will \
be redirected to the root directory \"/\"\n", 1);
		chdir("/");
		pwd = ft_strdup("/");
	}
	return (pwd);
}
