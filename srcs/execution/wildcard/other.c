/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 22:08:12 by oussama           #+#    #+#             */
/*   Updated: 2024/03/31 22:08:37 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

char	*ft_strstr(char *str, char *to_find)
{
	int	str_index;
	int	to_find_index;

	str_index = 0;
	to_find_index = 0;
	while (str && str[str_index] != '\0' && to_find[to_find_index] != '\0')
	{
		if (to_find[to_find_index] == str[str_index])
			to_find_index++;
		else
			to_find_index = 0;
		str_index++;
	}
	if (to_find_index == (int)ft_strlen(to_find))
		return (&str[str_index - to_find_index]);
	else
		return (NULL);
}
