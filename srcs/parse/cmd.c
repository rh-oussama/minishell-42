/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 22:08:22 by oussama           #+#    #+#             */
/*   Updated: 2024/03/31 22:09:17 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**fill_args(char **args)
{
	int		i;
	int		u;
	int		len;
	char	**data;

	len = 1;
	i = -1;
	while (args && args[++i])
		len++;
	data = malloc(sizeof(char *) * len);
	if (!data)
		return (NULL);
	i = 0;
	u = 0;
	while (args && args[i])
	{
		if (ft_strlen(args[i]) != 0)
			data[u++] = ft_strdup(args[i]);
		i++;
	}
	data[u] = NULL;
	return (data);
}

t_cmd	*create_command(char *data)
{
	t_cmd	*cmd;
	char	**args;

	args = ft_split_own(data);
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->in_red = fill_inred(args);
	cmd->out_red = fill_outred(args);
	if (g_ptr.parse.tmp_flag)
		return (NULL);
	cmd->args = fill_args(args);
	g_ptr.parse.tmp_flag = 0;
	free_split(args);
	return (cmd);
}
