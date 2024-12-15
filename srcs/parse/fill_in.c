/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_in.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 22:08:23 by oussama           #+#    #+#             */
/*   Updated: 2024/04/01 01:43:44 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_io	*ft_read_file(char *file)
{
	t_io	*head;
	char	*tmp;

	if (g_ptr.parse.tmp_flag)
		return (NULL);
	head = new_io_node(NULL, 'R');
	tmp = file;
	file = remove_quotation(file);
	head->file = ft_strdup(file);
	head->next = NULL;
	head->fd = -1;
	free(file);
	free(tmp);
	return (head);
}

char	*expand_infile(char *str)
{
	char	**tmp;

	tmp = malloc(sizeof(char *) * 2);
	if (!tmp)
		return (NULL);
	tmp[0] = ft_strdup(str);
	tmp[1] = NULL;
	handle_dollar_sign(&tmp);
	if (tmp[1])
	{
		free_split(tmp);
		g_ptr.parse.tmp_flag = 1;
		g_ptr.pstatus = ft_print_error("*", "ambiguous redirect2\n", 1);
		return (str);
	}
	str = ft_strdup(tmp[0]);
	free_split(tmp);
	return (str);
}

t_io	*fill_inred(char **args)
{
	t_io	*head;
	int		i;

	i = 0;
	head = NULL;
	while (args && args[i])
	{
		if (g_ptr.parse.tmp_flag)
			return (NULL);
		if (ft_strncmp(args[i], "<<", 3) == 0)
		{
			add_back_io(&head, ft_heredoc(args[i + 1]));
			args[i][0] = 0;
			args[i + 1][0] = 0;
		}
		else if (ft_strncmp(args[i], "<", 2) == 0)
		{
			add_back_io(&head, ft_read_file(wildcard_infile(expand_infile(args[i
							+ 1]))));
			args[i][0] = 0;
			args[i + 1][0] = 0;
		}
		i++;
	}
	return (head);
}

t_io	*ft_heredoc(char *limiter)
{
	t_io	*head;
	int		i;
	int		flag;

	if (g_ptr.parse.tmp_flag)
		return (NULL);
	flag = 0;
	i = -1;
	while (limiter && limiter[++i])
	{
		if (limiter && (limiter[i] == '"' || limiter[i] == '\''))
			flag = 1;
	}
	head = new_io_node(NULL, 'H');
	limiter = remove_quotation(limiter);
	head->file = read_heredoc(limiter, flag);
	head->next = NULL;
	head->fd = -1;
	return (head);
}
