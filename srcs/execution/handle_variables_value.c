/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_variables_value.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 22:07:32 by oussama           #+#    #+#             */
/*   Updated: 2024/04/02 01:26:12 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quots_value(t_cmd *cmd)
{
	int		i;
	int		j;
	char	**args;

	i = 1;
	j = 0;
	while (cmd->args && cmd->args[i])
		i++;
	args = malloc(sizeof(char *) * (i + 1));
	if (!args)
		return ;
	i = 0;
	while (cmd->args && cmd->args[i])
	{
		args[j] = quot_value(ft_strdup(cmd->args[i]), 0);
		if (args && args[j])
			j++;
		i++;
	}
	args[j] = NULL;
	free_split(cmd->args);
	cmd->args = args;
}

char	*quot_value(char *str, int flag)
{
	char	*new_str;
	int		i;

	i = 0;
	new_str = ft_strdup("");
	while (str && str[i])
	{
		if (str && str[i] == '\'')
			handle_single_quot(&new_str, &str[i], &i);
		else if (str && str[i] == '"')
			handle_double_quot(&new_str, &str[i], &i);
		else if (str && str[i] == '$' && str[i + 1] == '?' && flag == 0)
			handle_value(&new_str, &str[i], &i);
		else if (str && str[i] == '$' && (ft_isalpha(str[i + 1]) \
		|| str[i + 1] == '_' || str[i + 1] == '?') && flag == 1)
			handle_value(&new_str, &str[i], &i);
		else
			new_str = add_char_to_str(new_str, str[i]);
		i++;
	}
	if (str && ft_strlen(new_str) == 0 && str[0] != '"' && str[0] != '\'')
		return (free(str), free(new_str), NULL);
	free(str);
	return (new_str);
}

void	handle_value_hepler(char *str, char **new_str, int *index)
{
	char	*tmp;
	t_env	env;
	char	*key;

	key = ft_get_envkey(str);
	env = get_env_value(g_ptr.envp, key);
	if (env.value)
	{
		tmp = *new_str;
		*new_str = ft_strjoin(*new_str, env.value);
		free(tmp);
	}
	if (index)
		*index += ft_strlen(key);
	free(key);
}

void	handle_value(char **new_str, char *str, int *index)
{
	char	*tmp;
	char	*pstatus;
	int		i;

	i = 0;
	if (str && str[i] == '$')
	{
		i++;
		if (str && str[i] != '?')
			handle_value_hepler(str, new_str, index);
		else
		{
			pstatus = ft_itoa(g_ptr.pstatus);
			tmp = *new_str;
			*new_str = ft_strjoin(*new_str, pstatus);
			*index += 1;
			free(pstatus);
			free(tmp);
		}
	}
}
