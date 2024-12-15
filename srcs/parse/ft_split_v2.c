/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_v2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:52:48 by oussama           #+#    #+#             */
/*   Updated: 2024/03/31 22:26:36 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_validity.h"
#include <ctype.h>

char	**ft_split_own(char *str)
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
		else if (str && !isspace(str[i]))
			join_command(&arr, str, &i);
		else if (str && str[i])
			i++;
	}
	return (arr);
}
