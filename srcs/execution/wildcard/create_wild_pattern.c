/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_wild_pattern.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 03:04:48 by oussama           #+#    #+#             */
/*   Updated: 2024/03/31 22:56:56 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

void	create_node(char *str, char type, t_list **head)
{
	t_list	*tmp;
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return ;
	if (type != 'W')
		node->str = str;
	else
		node->str = ft_strdup(str);
	node->type = type;
	node->next = NULL;
	node->prev = NULL;
	if (*head == NULL)
		(*head) = node;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
		node->prev = tmp;
	}
}

char	*handle_other_2(char *str, int *i)
{
	int	j;
	int	l;

	j = *i;
	if (str && (str[*i] == '\"' || str[*i] == '\''))
	{
		l = skip_quotes_i(str, i);
		return (ft_strndup(&str[j + 1], l - 2));
	}
	else
	{
		while (str && str[*i] && str[*i] != '*' && str[*i] != '\"'
			&& str[*i] != '\'')
			(*i)++;
		return (ft_strndup(&str[j], (*i) - (j)));
	}
}

void	handle_other(char *str, int *i, t_list **head)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = NULL;
	while (str && str[*i] != '*' && str[*i] != '\0')
	{
		tmp3 = handle_other_2(str, i);
		tmp2 = ft_strjoin_g(tmp, tmp3);
		free(tmp);
		free(tmp3);
		tmp = tmp2;
	}
	if (ft_strlen(tmp))
		create_node(tmp, 'S', head);
	else
		free(tmp);
}

int	check_dir(t_list *head)
{
	char	*tmp2;
	int		i;
	int		dir;

	i = 0;
	dir = 0;
	if (!head)
		return (1);
	while (head->next)
		head = head->next;
	if (head->type != 'S')
		return (0);
	i = ft_strlen(head->str);
	i--;
	while (i >= 0 && (head->str)[i] == '/')
	{
		i--;
		dir++;
	}
	if (!dir)
		return (0);
	tmp2 = ft_strndup(head->str, i + 1);
	free(head->str);
	head->str = tmp2;
	return (1);
}

int	creat_wild(char *str, t_list **h)
{
	int		i;
	t_list	*head;
	t_list	*tmp;

	i = 0;
	head = NULL;
	while (str && str[i])
	{
		if (str && str[i] == '*')
		{
			while (str && str[i] && str[i] == '*')
				i++;
			tmp = head;
			while (tmp && tmp->next != NULL)
				tmp = tmp->next;
			if (tmp == NULL || tmp->type == 'S')
				create_node("*", 'W', &head);
		}
		else
			handle_other(str, &i, &head);
	}
	(*h) = head;
	return (check_dir(head));
}
