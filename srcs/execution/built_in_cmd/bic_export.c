/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bic_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 18:02:40 by oussama           #+#    #+#             */
/*   Updated: 2024/03/31 22:06:21 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

char	*sort_env_print(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		printf("declare -x %s\n", env[i]);
		free(env[i]);
		i++;
	}
	free(env);
	return (NULL);
}

void	sort_env(void)
{
	char	**env;
	int		i;
	int		j;
	char	*tmp;

	env = envp_dup(g_ptr.envp);
	j = 0;
	while (env && env[j])
	{
		i = 0;
		while (env && env[i] && env[i + 1])
		{
			if (env && ft_strcmp(env[i], env[i + 1]) > 0)
			{
				tmp = env[i];
				env[i] = env[i + 1];
				env[i + 1] = tmp;
			}
			i++;
		}
		j++;
	}
	sort_env_print(env);
}

size_t	str_poi(char *start, char *end)
{
	size_t	i;

	i = 0;
	if (!start || !end)
		return (-1);
	while (start && *start != '\0' && start != end)
	{
		i++;
		start++;
	}
	return (i);
}

void	var_not_found(char *cmd, int i, char *var_name)
{
	int		j;
	char	**tmp;

	j = 0;
	tmp = (char **)malloc(sizeof(char *) * (i + 2));
	if (!tmp)
		return ;
	while (cmd && *cmd && *cmd != '=')
		cmd++;
	tmp[0] = ft_strjoin_g(var_name, cmd);
	while (j < i)
	{
		tmp[j + 1] = g_ptr.envp[j];
		j++;
	}
	tmp[j + 1] = NULL;
	free(g_ptr.envp);
	g_ptr.envp = tmp;
}

char	*append_exp_var(int append, char *cmd, t_env tmp_env, char *var_name)
{
	char	*str;

	if (append == 2)
	{
		while (cmd && *cmd && *cmd != '=')
			cmd++;
		cmd++;
		str = ft_strjoin_g(g_ptr.envp[tmp_env.i], cmd);
		free(g_ptr.envp[tmp_env.i]);
		return (str);
	}
	else
	{
		while (cmd && *cmd && *cmd != '=')
			cmd++;
		str = ft_strjoin_g(var_name, cmd);
		free(g_ptr.envp[tmp_env.i]);
		return (str);
	}
}
