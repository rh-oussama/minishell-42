/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 22:08:50 by oussama           #+#    #+#             */
/*   Updated: 2024/03/31 21:40:56 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_validity.h"
#include "minishell.h"

int	is_operator(char *data, int index)
{
	int	i;
	int	dq;
	int	sq;
	int	pr;

	initialize_with_0(&dq, &sq, &pr);
	i = -1;
	while (data && data[++i] && i < index)
	{
		if (data && data[i] == '"' && dq == 0)
			dq++;
		else if (data && data[i] == '"' && dq)
			dq--;
		if (data && data[i] == '\'' && sq == 0)
			sq++;
		else if (data && data[i] == '\'' && sq)
			sq--;
		if (data && data[i] == '(')
			pr++;
		else if (data && data[i] == ')')
			pr--;
	}
	if (sq == 0 && dq == 0 && pr == 0)
		return (1);
	return (0);
}

int	just_white_spaces(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

char	*ft_theme(void)
{
	char	*text_in;
	char	*cwd;
	int		len;

	cwd = ft_getpwd();
	len = 44 + ft_strlen(cwd) + 1;
	text_in = ft_calloc(sizeof(char), len);
	ft_strlcat(text_in, BRIGHTCYAN, len);
	ft_strlcat(text_in, "☁  ", len);
	ft_strlcat(text_in, LIGTHGREEN, len);
	ft_strlcat(text_in, cwd, len);
	ft_strlcat(text_in, RESET, len);
	ft_strlcat(text_in, "  ", len);
	free(cwd);
	return (text_in);
}

void	free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	*ft_add_nl(char *str)
{
	char	*new;

	new = ft_strdup(str);
	ft_strlcat(new, "\n", ft_strlen(new) + 2);
	free(str);
	return (new);
}
