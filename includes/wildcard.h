/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 22:06:07 by oussama           #+#    #+#             */
/*   Updated: 2024/03/30 22:53:26 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <dirent.h>
# include "minishell.h"
# include "libft.h"

typedef struct s_list
{
	char			*str;
	char			type;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;

int		skip_quotes_i(char *str, int *i);
int		creat_wild(char *str, t_list **head);
int		check_wild(char *str, t_list *head);
int		compare_strings(char **str, t_list *tmp);
char	*ft_strstr(char *str, char *to_find);
char	*handle_other_2(char *str, int *i);
char	**lst_file(t_list *head, int d_ir);
char	*ft_strjoin_g(char const *s1, char const *s2);
void	create_node(char *str, char type, t_list **head);
void	handle_other(char *str, int *i, t_list **head);
void	add_back_list(char ***arr, char *str);
void	free_list(t_list *head);

#endif