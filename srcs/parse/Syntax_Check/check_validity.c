/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_validity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:31:03 by oussama           #+#    #+#             */
/*   Updated: 2024/03/31 22:13:02 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_validity.h"

int	check_parentheses_validity_2(char **str)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(*str))
	{
		if (*str && (**str == '\'' || **str == '\"'))
			skip_quotes(str);
		else if (*str && (**str == '|' || **str == '&'))
		{
			if (check_parentheses_validity_3(str) == 0)
				return (FALSE);
		}
		(*str)++;
		i++;
	}
	return (TRUE);
}

int	check_parentheses_validity(char *str)
{
	int	i_list[3];

	initialize_with_0(&i_list[0], &i_list[1], &i_list[2]);
	while (str && str[i_list[2]])
	{
		if (str && (str[i_list[2]] == '\'' || str[i_list[2]] == '\"'))
			skip_quotes_i(str, &i_list[2]);
		else if (str && str[i_list[2]] == '(')
		{
			i_list[0]++;
			i_list[2]++;
		}
		else if (str && str[i_list[2]] == ')')
		{
			i_list[1]++;
			i_list[2]++;
		}
		else
			i_list[2]++;
		if (i_list[1] > i_list[0])
			return (0);
	}
	if (i_list[0] != i_list[1] || !check_parentheses_validity_2(&str))
		return (FALSE);
	return (TRUE);
}

void	check_quotes_validity_2(char **str, int *sing, int *doub)
{
	char	c;

	c = **str;
	if (c == '\'')
		(*sing)++;
	else if (c == '\"')
		(*doub)++;
	(*str)++;
	while (*str && **str != '\0')
	{
		if (**str == c)
		{
			if (c == '\'')
				(*sing)++;
			else if (c == '\"')
				(*doub)++;
			(*str)++;
			return ;
		}
		(*str)++;
	}
}

int	check_quotes_validity(char *str)
{
	int	sing;
	int	doub;

	sing = 0;
	doub = 0;
	while (str && *str)
	{
		if (str && (*str == '\'' || *str == '\"'))
			check_quotes_validity_2(&str, &sing, &doub);
		else if (*str)
			str++;
	}
	if (sing % 2 == 0 && doub % 2 == 0)
		return (TRUE);
	return (FALSE);
}

int	check_syntax_validity(char *str)
{
	if (!str)
		return (0);
	if (!check_quotes_validity(str))
		return (1);
	if (!check_parentheses_validity(str))
		return (55);
	if (!check_syntax_v2(str))
		return (3);
	return (0);
}
