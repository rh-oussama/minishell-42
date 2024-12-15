/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_variables_value_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 22:07:30 by oussama           #+#    #+#             */
/*   Updated: 2024/03/31 22:03:34 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_envkey(char *str)
{
	int		i;
	char	*key;

	i = 1;
	while (str && str[i] && (ft_isalnum(str[i]) || str[i] == '_')
		&& !ft_isspace(str[i]))
		i++;
	key = malloc(sizeof(char) * i + 1);
	if (!key)
		return (NULL);
	i = 1;
	while (str && str[i] && (ft_isalnum(str[i]) || str[i] == '_')
		&& !ft_isspace(str[i]))
	{
		key[i - 1] = str[i];
		key[++i - 1] = '\0';
	}
	return (key);
}

t_env	get_env_value(char **envp, char *to)
{
	int		i;
	int		j;
	char	*tmp;
	t_env	tmp_env;

	i = 0;
	j = 0;
	j = ft_strlen(to) + 1;
	tmp = ft_strjoin(to, "=");
	tmp_env.i = 0;
	tmp_env.value = NULL;
	while (envp && envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], tmp, j) == 0)
		{
			tmp_env.i = i;
			tmp_env.value = envp[i] + j;
			break ;
		}
		i++;
	}
	free(tmp);
	return (tmp_env);
}

char	*add_char_to_str(char *str, char c)
{
	char	*new_str;
	char	s[2];
	int		len;

	if (!str)
	{
		s[0] = c;
		s[1] = 0;
		return (ft_strdup(s));
	}
	new_str = ft_calloc(sizeof(char), (ft_strlen(str) + 2));
	ft_strlcat(new_str, str, ft_strlen(str) + 1);
	len = ft_strlen(new_str);
	new_str[len] = c;
	new_str[len + 1] = 0;
	free(str);
	return (new_str);
}

char	**split_max(char *str)
{
	char	**args;
	char	*tmp;
	int		i;

	i = 0;
	args = NULL;
	tmp = NULL;
	while (str && str[i])
	{
		if (str && str[i] && !ft_isspace(str[i]))
		{
			tmp = get_str_max(str, &i);
			add_back_list(&args, tmp);
			free(tmp);
		}
		else if (str && str[i])
			i++;
	}
	return (args);
}
