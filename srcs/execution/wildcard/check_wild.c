/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wild.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 02:23:17 by oussama           #+#    #+#             */
/*   Updated: 2024/04/02 01:24:50 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

int	compare_strings(char **str, t_list *tmp)
{
	char	*found;

	if (tmp->prev && tmp->next && tmp->prev->type == 'W'
		&& tmp->next->type == 'W')
	{
		found = ft_strstr(*str, tmp->str);
		if (!found)
			return (0);
		*str = found + ft_strlen(tmp->str);
	}
	else if (tmp->prev && !tmp->next && tmp->prev->type == 'W')
	{
		if (ft_strcmp(*str + ft_strlen(*str) - ft_strlen(tmp->str),
				tmp->str) != 0)
			return (0);
		*str += ft_strlen(*str);
	}
	else if (tmp->next && !tmp->prev && tmp->next->type == 'W')
	{
		if (ft_strncmp(*str, tmp->str, ft_strlen(tmp->str)) != 0)
			return (0);
		*str += ft_strlen(tmp->str);
	}
	return (1);
}

int	check_wild(char *str, t_list *head)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = head;
	while (tmp)
	{
		if (tmp->type == 'W')
			i++;
		tmp = tmp->next;
	}
	if (i == 0)
		return (0);
	tmp = head;
	while (tmp)
	{
		if (!compare_strings(&str, tmp))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void	add_back_list(char ***arr, char *str)
{
	char	**tmp;
	char	**tmp2;
	int		i;

	tmp = *arr;
	i = 0;
	while (tmp && tmp[i++])
		;
	tmp2 = malloc(sizeof(char *) * (i + 2));
	if (!tmp2)
		return ;
	i = 0;
	while (tmp && tmp[i])
	{
		tmp2[i] = tmp[i];
		i++;
	}
	tmp2[i] = ft_strdup(str);
	tmp2[i + 1] = NULL;
	free(*arr);
	*arr = tmp2;
}

char	**lst_file_helper(struct dirent *entry, t_list *head, int d_ir,
		char **arr)
{
	char	*tmp;

	if (ft_strcmp(entry->d_name, ".") && ft_strcmp(entry->d_name, "..")
		&& ft_strncmp(entry->d_name, ".", 1))
	{
		if (check_wild(entry->d_name, head) == 1)
		{
			if (d_ir == 1 && entry->d_type == DT_DIR)
			{
				tmp = ft_strjoin_g(entry->d_name, "/");
				add_back_list(&arr, tmp);
				free(tmp);
			}
			else if (d_ir == 0)
				add_back_list(&arr, entry->d_name);
		}
	}
	return (arr);
}

char	**lst_file(t_list *head, int d_ir)
{
	char			**arr;
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(".");
	if (!dir)
		return (NULL);
	arr = NULL;
	if (!dir)
		return (NULL);
	entry = readdir(dir);
	if (!entry)
		return (NULL);
	while (entry != NULL)
	{
		arr = lst_file_helper(entry, head, d_ir, arr);
		entry = readdir(dir);
	}
	if (closedir(dir) == -1)
		perror("closedir");
	return (arr);
}
