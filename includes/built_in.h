/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 22:05:41 by oussama           #+#    #+#             */
/*   Updated: 2024/03/30 22:23:35 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "minishell.h"
# include "libft.h"

int		exp_validity_1(char *cmd);
int		exp_validity_2(char *cmd);
int		check_validity(char *pos, char *cmd, size_t *var_length);
size_t	str_poi(char *start, char *end);
char	*sort_env_print(char **env);
char	*append_exp_var(int append, char *cmd, t_env tmp_env, char *var_name);
void	assig_value_env(char *cmd, char *var_name, int append);
void	sort_env(void);
void	var_not_found(char *cmd, int i, char *var_name);
void	export_var(char **cmd);

#endif