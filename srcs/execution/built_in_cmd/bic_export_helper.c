/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bic_export_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 18:02:34 by oussama           #+#    #+#             */
/*   Updated: 2024/03/31 22:05:15 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

void	assig_value_env(char *cmd, char *var_name, int append)
{
	t_env	tmp_env;
	int		i;

	i = 0;
	while (g_ptr.envp && g_ptr.envp[i])
		i++;
	tmp_env = get_env_value(g_ptr.envp, var_name);
	if (tmp_env.value == NULL)
		var_not_found(cmd, i, var_name);
	else
	{
		g_ptr.envp[tmp_env.i] = append_exp_var(append, cmd, tmp_env, var_name);
	}
}

int	exp_validity_1(char *cmd)
{
	int		i;
	char	*str;

	i = 0;
	while (cmd && cmd[i] && cmd[i] != '=')
		i++;
	if (!isalpha(cmd[0]) && cmd[0] != '_')
		return (0);
	if (i > 1 && cmd[i - 1] == '+')
		i--;
	str = ft_strndup(cmd, i);
	i = 1;
	while (str && str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			free(str);
			return (0);
		}
		i++;
	}
	free(str);
	return (1);
}

int	exp_validity_2(char *cmd)
{
	int	i;

	i = 0;
	while (cmd && cmd[i])
	{
		if ((!ft_isalnum(cmd[i]) && cmd[i] != '_') || ft_isdigit(cmd[0]))
		{
			ft_putendl_fd("minishell: export: : not a valid identifier", 2);
			g_ptr.pstatus = 1;
			return (0);
		}
		i++;
	}
	g_ptr.pstatus = 0;
	return (0);
}

int	check_validity(char *pos, char *cmd, size_t *var_length)
{
	if (pos == NULL)
	{
		exp_validity_2(cmd);
		return (0);
	}
	while (cmd[(*var_length)] && cmd[(*var_length)] != '=')
		(*var_length)++;
	if (*var_length == 0 || !exp_validity_1(cmd))
	{
		ft_putendl_fd("minishell: export: : not a valid identifier", 2);
		g_ptr.pstatus = 1;
		return (0);
	}
	if ((*var_length) > 1 && cmd[(*var_length) - 1] == '+')
	{
		(*var_length)--;
		return (2);
	}
	return (1);
}

void	export_var(char **cmd)
{
	int		i;
	char	*pos_var_name[2];
	int		append;
	size_t	var_length;

	i = 1;
	if (cmd && !cmd[i])
		sort_env();
	while (cmd && cmd[i] != NULL)
	{
		var_length = 0;
		pos_var_name[0] = ft_strchr(cmd[i], '=');
		append = check_validity(pos_var_name[0], cmd[i], &var_length);
		if (append)
		{
			pos_var_name[1] = ft_strndup(cmd[i], var_length);
			assig_value_env(cmd[i], pos_var_name[1], append);
			free(pos_var_name[1]);
		}
		i++;
	}
}
