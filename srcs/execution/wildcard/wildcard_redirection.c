/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 22:08:14 by oussama           #+#    #+#             */
/*   Updated: 2024/04/02 01:24:25 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

char	*wildcard_infile(char *str)
{
	char	**tmp;
	char	*new;
	t_list	*head;

	if (g_ptr.parse.tmp_flag)
		return (str);
	creat_wild(str, &head);
	tmp = lst_file(head, 0);
	free_list(head);
	if (tmp)
	{
		if (tmp[1])
		{
			free_split(tmp);
			g_ptr.parse.tmp_flag = 1;
			g_ptr.pstatus = ft_print_error("*", "ambiguous redirect1\n", 1);
			return (str);
		}
		new = ft_strdup(tmp[0]);
		free(str);
		free_split(tmp);
		return (new);
	}
	return (str);
}

char	*ft_strjoin_g(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
		str[i++] = s2[j++];
	str[i] = 0;
	return (str);
}
