/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bic_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:45:42 by orhaddao          #+#    #+#             */
/*   Updated: 2024/03/31 16:00:23 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printf_env(void)
{
	char	**envp;

	envp = g_ptr.envp;
	while (*envp)
	{
		ft_putendl_fd(*envp, 1);
		envp++;
	}
	g_ptr.pstatus = 0;
}
