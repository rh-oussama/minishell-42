/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 22:06:04 by oussama           #+#    #+#             */
/*   Updated: 2024/03/30 22:33:16 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "parse.h"
# include "execution.h"
# include "libft.h"
# include "wildcard.h"

typedef struct s_ptr
{
	t_parse	parse;
	char	**envp;
	int		pstatus;
}	t_ptr;

extern t_ptr	g_ptr;

void	parse(void);
void	execution(void);
void	clean(void);
void	clean_all(void);
int		ft_print_error(char *str, char *error, int n);

#endif