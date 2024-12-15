/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bic_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 22:07:57 by oussama           #+#    #+#             */
/*   Updated: 2024/03/30 22:07:58 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_cwd(void)
{
	char	*str;

	str = ft_getpwd();
	if (!str)
	{
		perror("getcwd");
		return ;
	}
	printf("%s\n", str);
	g_ptr.pstatus = 0;
	free(str);
}
