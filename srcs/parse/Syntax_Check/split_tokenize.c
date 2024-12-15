/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:52:48 by oussama           #+#    #+#             */
/*   Updated: 2024/03/31 22:28:23 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_validity.h"
#include <ctype.h>

int	skip_quotes_i(char *str, int *i)
{
	int		count;
	char	quote;

	count = 2;
	quote = str[*i];
	(*i)++;
	while (str && str[*i] != quote && str[*i] != '\0')
	{
		(*i)++;
		count++;
	}
	if (str && str[*i] == quote)
		(*i)++;
	return (count);
}

void	join_str(char ***arr, char *str)
{
	int		i;
	int		j;
	char	**new_arr;

	i = 0;
	j = 0;
	while ((*arr) && (*arr)[i] != NULL)
		i++;
	new_arr = malloc(sizeof(char *) * (i + 2));
	if (!new_arr)
		return ;
	while (j < i)
	{
		new_arr[j] = (*arr)[j];
		j++;
	}
	new_arr[i] = str;
	new_arr[i + 1] = NULL;
	if (*arr)
		free(*arr);
	*arr = new_arr;
}

void	join_chars(char ***arr, char *str, int *i)
{
	char	c;
	char	*new_str;
	int		count;

	c = str[*i];
	count = 0;
	while (str && str[(*i)++] == c)
		count++;
	(*i)--;
	new_str = ft_strndup(str + (*i) - count, count);
	join_str(arr, new_str);
}

void	join_command(char ***arr, char *str, int *i)
{
	int		start;
	int		length;
	char	*new_str;

	start = *i;
	length = 0;
	while (str && str[*i] && (str[*i] != '(' && str[*i] != ')' && str[*i] != '<'
			&& str[*i] != '>' && str[*i] != '|' && str[*i] != '&'
			&& !ft_isspace(str[*i])))
	{
		if (str && (str[*i] == '\"' || str[*i] == '\''))
			length += skip_quotes_i(str, i);
		else if (str && str[*i])
		{
			(*i)++;
			length++;
		}
	}
	new_str = ft_strndup(str + start, length);
	join_str(arr, new_str);
}

char	**split_tokenize(char *str)
{
	char	**arr;
	int		i;

	arr = NULL;
	i = 0;
	while (str && str[i])
	{
		if (str && (str[i] == '(' || str[i] == ')'))
			join_str(&arr, ft_strndup(str + i++, 1));
		else if (str && (str[i] == '<' || str[i] == '>' || str[i] == '&'
				|| str[i] == '|'))
			join_chars(&arr, str, &i);
		else if (str && !ft_isspace(str[i]))
			join_command(&arr, str, &i);
		else if (str && str[i])
			i++;
	}
	return (arr);
}
