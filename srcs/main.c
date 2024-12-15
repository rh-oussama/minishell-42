/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 22:07:10 by oussama           #+#    #+#             */
/*   Updated: 2024/03/30 22:07:11 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ptr	g_ptr;

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	if (argc > 1)
	{
		ft_putendl_fd("[minishell] Does not take arguments!", 2);
		return (1);
	}
	init_ptr(envp);
	while (1)
	{
		parse();
		execution();
		clean();
	}
	return (g_ptr.pstatus);
}
