/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_validity_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 23:33:47 by oussama           #+#    #+#             */
/*   Updated: 2024/04/02 01:27:10 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_validity.h"

int	get_type_v0(char *str)
{
	while (str && *str != '\0')
	{
		if (str && (*str == '\"' || *str == '\''))
			skip_quotes(&str);
		else if (str && (*str == '<' || *str == '>'))
			return (REDIRICTION);
		else if (str && (*str == '|' || *str == '&'))
			return (OPERATOR);
		else if (str && *str == '(')
			return (P_OPEN);
		else if (str && *str == ')')
			return (P_CLOSE);
		else if (*str)
			str++;
	}
	return (STRING);
}

int	check_operator_syntax(char **arr, int i)
{
	if (arr && (i == 0 || arr[i + 1] == NULL))
		return (FALSE);
	if (arr && get_type_v0(arr[i - 1]) != STRING \
	&& get_type_v0(arr[i - 1]) != P_CLOSE)
		return (FALSE);
	if (arr && get_type_v0(arr[i + 1]) != STRING \
	&& get_type_v0(arr[i + 1]) != P_OPEN \
	&& get_type_v0(arr[i + 1]) != REDIRICTION)
		return (FALSE);
	return (TRUE);
}

int	check_par_syntax(char **arr, int i)
{
	if (arr && get_type_v0(arr[i]) == P_OPEN)
	{
		if (arr && (get_type_v0(arr[i + 1]) == OPERATOR \
		|| get_type_v0(arr[i + 1]) == P_CLOSE))
			return (FALSE);
		if (arr && i != 0 && (get_type_v0(arr[i - 1]) != OPERATOR \
		&& get_type_v0(arr[i - 1]) != P_OPEN))
			return (FALSE);
	}
	else
	{
		if (arr && arr[i + 1] != NULL && get_type_v0(arr[i + 1]) != OPERATOR \
		&& get_type_v0(arr[i + 1]) != P_CLOSE \
		&& get_type_v0(arr[i + 1]) != REDIRICTION)
			return (FALSE);
		if (arr && get_type_v0(arr[i - 1]) != STRING && \
		get_type_v0(arr[i - 1]) != P_CLOSE)
			return (FALSE);
	}
	return (TRUE);
}

int	check_syntax_helper(char **arr, int i)
{
	if (arr && get_type_v0(arr[i]) == REDIRICTION)
	{
		if (arr && (arr[i + 1] == NULL || get_type_v0(arr[i + 1]) != STRING))
			return (FALSE);
	}
	else if (arr && get_type_v0(arr[i]) == OPERATOR)
	{
		if (arr && check_operator_syntax(arr, i) == FALSE)
			return (FALSE);
	}
	else if (arr && (get_type_v0(arr[i]) == P_OPEN
			|| get_type_v0(arr[i]) == P_CLOSE))
	{
		if (arr && check_par_syntax(arr, i) == FALSE)
			return (FALSE);
	}
	return (TRUE);
}

int	check_syntax_v2(char *str)
{
	int		i;
	char	**arr;

	arr = split_tokenize(str);
	i = 0;
	while (arr && arr[i])
	{
		if (!check_syntax_helper(arr, i))
		{
			free_split(arr);
			return (FALSE);
		}
		i++;
	}
	free_split(arr);
	return (TRUE);
}
