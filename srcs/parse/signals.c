/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 22:08:38 by oussama           #+#    #+#             */
/*   Updated: 2024/03/30 22:08:39 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_heredoc(int n)
{
	(void)n;
	exit(255);
}

void	sigint_handle(int n)
{
	g_ptr.pstatus = 130;
	if (n == SIGINT && !g_ptr.parse.herdoc_flag)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		write(1, "\n", 1);
}

void	ft_magic(int n)
{
	(void)n;
}
