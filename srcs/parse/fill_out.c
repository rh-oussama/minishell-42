/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_out.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 22:08:25 by oussama           #+#    #+#             */
/*   Updated: 2024/04/01 01:41:05 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_io	*ft_out_file_appand(char *file)
{
	t_io	*new;
	char	*tmp;

	new = new_io_node(NULL, 'A');
	new->fd = -1;
	new->next = NULL;
	tmp = file;
	file = ft_strdup(file);
	new->file = remove_quotation(file);
	free(file);
	free(tmp);
	return (new);
}

t_io	*ft_out_file(char *file)
{
	t_io	*new;
	char	*tmp;

	new = new_io_node(NULL, 'O');
	new->fd = -1;
	new->next = NULL;
	tmp = file;
	file = ft_strdup(file);
	new->file = remove_quotation(file);
	free(file);
	free(tmp);
	return (new);
}

void	fill_outred_hepler(char **args, int i, t_io **head)
{
	if (ft_strncmp(args[i], ">>", 3) == 0)
	{
		add_back_io(head,
			ft_out_file_appand(wildcard_infile(expand_infile(args[i + 1]))));
		args[i][0] = 0;
		args[i + 1][0] = 0;
	}
	else if (ft_strncmp(args[i], ">", 2) == 0)
	{
		add_back_io(head, ft_out_file(wildcard_infile(expand_infile(args[i
						+ 1]))));
		args[i][0] = 0;
		args[i + 1][0] = 0;
	}
}

t_io	*fill_outred(char **args)
{
	t_io	*head;
	int		i;

	head = NULL;
	i = 0;
	while (args && args[i])
	{
		if (g_ptr.parse.tmp_flag)
			return (NULL);
		fill_outred_hepler(args, i, &head);
		i++;
	}
	return (head);
}
