/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_value_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orhaddao <orhaddao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 09:21:31 by oussama           #+#    #+#             */
/*   Updated: 2024/04/01 23:33:38 by orhaddao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_vname(char *var_name, char **str, int *j, t_env value)
{
	char	*tmp;
	char	*new_str;
	char	*tmp3;

	tmp = NULL;
	if (!var_name || !(value.value))
	{
		tmp = ft_strndup((*str), *j - ft_strlen(var_name) - 1);
		new_str = ft_strjoin_g(tmp, &((*str)[*j]));
		free(*str);
		*str = new_str;
		*j = *j - ft_strlen(var_name);
	}
	else
	{
		tmp = ft_strndup((*str), *j - ft_strlen(var_name) - 1);
		tmp3 = ft_strjoin_g(tmp, value.value);
		new_str = ft_strjoin_g(tmp3, &((*str)[*j]));
		free(*str);
		free(tmp3);
		*str = new_str;
		*j = *j - ft_strlen(value.value);
	}
	free(var_name);
	free(tmp);
}

void	handle_dollar_sign_2(char **str, int *j)
{
	char	*var_name;
	t_env	value;
	int		l;

	var_name = NULL;
	l = *j;
	(*j)++;
	while ((*str)[*j] && ((ft_isalnum((*str)[*j])) || (*str)[*j] == '_'))
		(*j)++;
	l = *j - l;
	if (l)
		var_name = ft_strndup(&((*str)[*j - l + 1]), l - 1);
	value = get_env_value(g_ptr.envp, var_name);
	update_vname(var_name, str, j, value);
}

void	handle_dollar_sign(char ***args)
{
	int	i;
	int	j;

	i = 0;
	while ((*args) && (*args)[i])
	{
		j = 0;
		while ((int)ft_strlen((*args)[i]) > j && (*args)[i][j])
		{
			if ((*args)[i][j] && ((*args)[i][j] == '\''
					|| (*args)[i][j] == '\"'))
				skip_quotes_i((*args)[i], &j);
			else if ((*args)[i][j] && (*args)[i][j] == '$' && (*args)[i][j + 1]
				&& (ft_isalpha((*args)[i][j + 1]) || (*args)[i][j + 1] == '_')
				&& (*args)[i][j + 1] != '?')
				handle_dollar_sign_2(&(*args)[i], &j);
			else if ((int)ft_strlen((*args)[i]) > j)
				j++;
		}
		i++;
	}
	handle_dollar_sign_3(args);
}

char	*get_str_max(char *str, int *i)
{
	int		s;
	char	*tmp;

	s = *i;
	while (str[*i] && !ft_isspace(str[*i]))
	{
		if (str && (str[*i] == '\'' || str[*i] == '\"'))
			skip_quotes_i(str, i);
		else if (str && str[*i])
			(*i)++;
	}
	tmp = ft_strndup(&str[s], *i - s);
	return (tmp);
}

void	handle_dollar_sign_3(char ***args)
{
	int		i;
	char	**tmp;

	tmp = NULL;
	i = 0;
	while (args && (*args) && (*args)[i])
	{
		tmp = split_max((*args)[i]);
		if (tmp)
			insert_wild(tmp, args, i);
		free(tmp);
		i++;
	}
}
