/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_utils_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:53:55 by oussama           #+#    #+#             */
/*   Updated: 2024/03/31 22:12:17 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_validity.h"

void	skip_quotes(char **str)
{
	char	quote;

	if (!str)
		return ;
	if (!(*str))
		return ;
	quote = **str;
	(*str)++;
	while (*str && **str != quote && **str != '\0')
		(*str)++;
	if (**str == quote)
		(*str)++;
}

int	check_parentheses_validity_3(char **str)
{
	int		i;
	char	c;

	i = 0;
	c = **str;
	while (*str && **str == c)
	{
		i++;
		(*str)++;
	}
	(*str)--;
	if (c == '&' && i != 2)
		return (FALSE);
	if (c == '|' && i > 2)
		return (FALSE);
	return (TRUE);
}

void	initialize_with_0(int *i1, int *i2, int *i3)
{
	*i1 = 0;
	*i2 = 0;
	*i3 = 0;
}
