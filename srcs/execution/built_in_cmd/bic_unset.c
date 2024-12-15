/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bic_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:09:18 by orhaddao          #+#    #+#             */
/*   Updated: 2024/03/31 22:06:53 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_var(t_env tmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (g_ptr.envp && g_ptr.envp[i])
	{
		if (i == tmp.i)
			free(g_ptr.envp[i]);
		else
			g_ptr.envp[j++] = g_ptr.envp[i];
		i++;
	}
	g_ptr.envp[j] = NULL;
}

void	unset_var(char **cmd)
{
	int		i;
	t_env	tmp;

	i = 1;
	while (cmd && cmd[i])
	{
		tmp.i = 0;
		tmp.value = NULL;
		tmp = get_env_value(g_ptr.envp, cmd[i]);
		if (tmp.value != NULL)
			delete_var(tmp);
		i++;
	}
	g_ptr.pstatus = 0;
}
