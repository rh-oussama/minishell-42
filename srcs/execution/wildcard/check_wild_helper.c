/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wild_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:56:13 by oussama           #+#    #+#             */
/*   Updated: 2024/03/31 01:38:14 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

void	inset_wild_helper(char **arr, char **arg, int *i, int *l)
{
	(*i) = 0;
	(*l) = 0;
	while (arr && arr[(*i)])
	{
		(*i)++;
	}
	while (arg && arg[(*l)])
	{
		(*l)++;
		(*i)++;
	}
	(*l) = 0;
}

void	insert_wild(char **arr, char ***arg, int j)
{
	int		i;
	int		l;
	char	**tmp;

	inset_wild_helper(arr, *arg, &i, &l);
	tmp = malloc(sizeof(char *) * (i + 1));
	if (!tmp)
		return ;
	i = 0;
	while ((*arg) && (*arg)[i] && i < j)
	{
		tmp[i] = (*arg)[i];
		i++;
	}
	l = 0;
	while (arr && arr[l])
		tmp[i++] = arr[l++];
	free((*arg)[j++]);
	while ((*arg) && (*arg)[j])
		tmp[i++] = (*arg)[j++];
	tmp[i] = NULL;
	free(*arg);
	(*arg) = tmp;
}

void	apply_wild_card(char ***arg)
{
	char	**tmp;
	int		dir;
	int		i;
	t_list	*head;

	i = 0;
	while ((*arg) && (*arg)[i])
	{
		dir = creat_wild((*arg)[i], &head);
		tmp = lst_file(head, dir);
		if (tmp && *tmp)
			insert_wild(tmp, arg, i);
		free(tmp);
		free_list(head);
		i++;
	}
}

void	free_list(t_list *head)
{
	t_list	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->str);
		free(tmp);
	}
}
