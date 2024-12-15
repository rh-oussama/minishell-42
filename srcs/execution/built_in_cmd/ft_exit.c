/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:03:07 by oussama           #+#    #+#             */
/*   Updated: 2024/03/31 21:56:49 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_str2int(char *str)
{
	int	n;
	int	i;
	int	s;

	n = 0;
	i = 0;
	s = 0;
	while (str && str[i] && ft_isspace(str[i]))
		i++;
	if (str && str[i] && str[i] == '-')
		s++;
	if (str && str[i] && (str[i] == '+' || str[i] == '-'))
		i++;
	while (str && (str[i] || !str[0]))
	{
		if (str && (ft_isdigit(str[i]) == 0 || !str[0]))
			return (ft_putendl_fd(\
"minishell: exit: A: numeric argument required", 2), 2);
		if (str && ft_isdigit(str[i]))
			n = (n * 10) + (str[i] - '0');
		i++;
	}
	if (s % 2)
		return (-n);
	return (n);
}

void	ft_exit(char **cmd)
{
	int	i;
	int	ps;

	i = 0;
	while (cmd && cmd[i])
		i++;
	printf("exit\n");
	if (i <= 1)
	{
		clean_all();
		exit(g_ptr.pstatus % 255);
	}
	else if (i >= 2)
	{
		if (i > 2)
		{
			ft_putendl_fd("minishell: exit: too many arguments", 2);
			g_ptr.pstatus = 1;
			return ;
		}
		ps = ft_str2int(cmd[1]);
		clean_all();
		exit(ps);
	}
}
