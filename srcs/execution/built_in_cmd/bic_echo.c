/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bic_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:37:16 by orhaddao          #+#    #+#             */
/*   Updated: 2024/04/02 01:26:43 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dd(char *str)
{
	int	n;
	int	i;

	n = 0;
	i = 0;
	if (!str)
		return (0);
	if (str[i] && str[i] == '-')
	{
		i++;
		while (str[i] && str[i] == 'n')
			i++;
		if (str[i] == '\0')
			n = 1;
	}
	return (n);
}

void	echo_handler(char **cmd)
{
	int	i;
	int	n;

	i = 1;
	n = dd(cmd[1]);
	while (cmd && dd(cmd[i]))
		i++;
	while (cmd && cmd[i])
	{
		printf("%s", cmd[i]);
		i++;
		if (cmd[i] != NULL)
			printf(" ");
	}
	if (cmd && !n)
		printf("\n");
	g_ptr.pstatus = 0;
}
