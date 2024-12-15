/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 22:08:33 by oussama           #+#    #+#             */
/*   Updated: 2024/03/31 00:56:44 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_input(void)
{
	if (!ft_strlen(g_ptr.parse.row_data)
		|| just_white_spaces(g_ptr.parse.row_data))
	{
		free(g_ptr.parse.row_data);
		g_ptr.parse.tmp_flag = 1;
		return (1);
	}
	if (check_syntax_validity(g_ptr.parse.row_data))
	{
		free(g_ptr.parse.row_data);
		g_ptr.pstatus = ft_print_error("! ", "Syntax error\n", 2);
		g_ptr.parse.tmp_flag = 1;
		return (1);
	}
	return (0);
}

void	add_it_on_env(char *key, char *value)
{
	char	**tmp;
	char	*arg;
	char	*tmp2;

	tmp = malloc(sizeof(char *) * 3);
	if (!tmp)
		return ;
	tmp2 = ft_strjoin(key, "=");
	arg = ft_strjoin(tmp2, value);
	free(tmp2);
	tmp[0] = ft_strdup("export");
	tmp[1] = arg;
	tmp[2] = NULL;
	export_var(tmp);
	free_split(tmp);
}

void	ft_underscore(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	if (i > 0)
		i--;
	g_ptr.parse.underscore = ft_strdup(args[i]);
}

void	parse(void)
{
	char	*text_in;

	signal(SIGINT, sigint_handle);
	if (g_ptr.parse.underscore)
	{
		add_it_on_env("_", g_ptr.parse.underscore);
		free(g_ptr.parse.underscore);
		g_ptr.parse.underscore = NULL;
	}
	g_ptr.parse.tmp_flag = 0;
	text_in = ft_theme();
	g_ptr.parse.row_data = readline(text_in);
	free(text_in);
	if (!g_ptr.parse.row_data)
		ft_exit(NULL);
	if (check_input())
		return ;
	add_history(g_ptr.parse.row_data);
	g_ptr.parse.data = split_and_or(g_ptr.parse.row_data);
	free(g_ptr.parse.row_data);
	create_aolist();
}
