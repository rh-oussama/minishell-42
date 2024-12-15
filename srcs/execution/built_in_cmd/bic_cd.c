/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bic_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:56:03 by orhaddao          #+#    #+#             */
/*   Updated: 2024/03/31 22:04:44 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_curent_pwd(void)
{
	t_env	tmp_env;
	char	*cu;
	char	*new_pwd;

	cu = ft_getpwd();
	if (!cu)
		return ;
	tmp_env = get_env_value(g_ptr.envp, "PWD");
	if (tmp_env.value == NULL)
		return ;
	new_pwd = ft_strjoin_g("PWD=", cu);
	free(g_ptr.envp[tmp_env.i]);
	free(cu);
	g_ptr.envp[tmp_env.i] = new_pwd;
}

void	var_not_found_cd(char *old_pwd, int i)
{
	char	**tmp;
	int		j;

	j = 0;
	tmp = (char **)malloc(sizeof(char *) * (i + 2));
	if (!tmp)
		return ;
	tmp[0] = ft_strjoin_g("OLDPWD=", old_pwd);
	while (j < i)
	{
		tmp[j + 1] = g_ptr.envp[j];
		j++;
	}
	tmp[j + 1] = NULL;
	free(g_ptr.envp);
	g_ptr.envp = tmp;
}

void	update_cwd(char *old_pwd)
{
	t_env	tmp_env;
	int		i;

	i = 0;
	while (g_ptr.envp[i] != NULL)
		i++;
	tmp_env = get_env_value(g_ptr.envp, "OLDPWD");
	if (tmp_env.value == NULL)
		var_not_found_cd(old_pwd, i);
	else
	{
		free(g_ptr.envp[tmp_env.i]);
		g_ptr.envp[tmp_env.i] = ft_strjoin_g("OLDPWD=", old_pwd);
	}
}

void	cd_handler(char **cmd)
{
	t_env	tmp_env;
	char	*oldcwd;
	char	*tmp;
	int		i;

	i = 0;
	tmp_env = get_env_value(g_ptr.envp, "HOME");
	tmp = ft_getpwd();
	if (!tmp)
		return ;
	oldcwd = ft_strdup(tmp);
	free(tmp);
	while (cmd && cmd[i] != NULL)
		i++;
	if (i > 2)
	{
		g_ptr.pstatus = ft_print_error("cd", "too many arguments\n", 1);
		free(oldcwd);
		return ;
	}
	else if (i == 1)
		cd_handle_home(tmp_env, oldcwd);
	else if (i == 2)
		cd_handle_path(cmd, oldcwd);
	free(oldcwd);
}
