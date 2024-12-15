/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 22:05:59 by oussama           #+#    #+#             */
/*   Updated: 2024/03/30 22:30:57 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

typedef struct s_fdbackup
{
	int	in;
	int	out;
}	t_fdbackup;

typedef struct s_env
{
	int		i;
	char	*value;
}	t_env;

t_env	get_env_value(char **envp, char *to);
char	**envp_dup(char **envp);
char	*get_final_path(char *command);
char	*ft_get_envkey(char *str);
char	**split_max(char *str);
char	*get_str_max(char *str, int *i);
int		apply_redirections(t_cmd *cmd);
int		apply_outredirections(t_io *io);
int		apply_inredirections(t_io *io);
int		ft_fork(void);
int		is_directory(char *path);
int		is_file(char *path);
int		open_outredirections(t_io *io);
int		open_inredirections(t_io *io);
void	fdbackup(t_fdbackup *backup);
void	default_io(t_fdbackup backup);
void	handle_quots_value(t_cmd *cmd);
void	ft_print_cwd(void);
char	*ft_getpwd(void);
void	apply_wild_card(char ***arg);
void	check_file(char *command);
void	cd_handle_home(t_env tmp_env, char *oldpwd);
void	cd_handle_path(char **cmd, char *oldpwd);
void	update_curent_pwd(void);
void	var_not_found_cd(char *old_pwd, int i);
void	update_cwd(char *old_pwd);
void	cd_handler(char **cmd);
void	clean(void);
void	echo_handler(char **cmd);
void	printf_env(void);
void	export_var(char **cmd);
void	unset_var(char **cmd);
void	ft_exit(char **cmd);
void	free_tree(t_aolist *tree);
void	sigint_handle(int n);
void	ft_magic(int n);
void	handle_dollar_sign(char ***args);
void	execute_tree(t_aolist *tree);
void	execute_pipe(t_plist *head);
void	execute(char **args, int parent);
void	execute_command(t_cmd *cmd, int parent);
void	join_fd(int **fd_arr, int fd);
void	close_fd(int *fd_arr);
void	handle_dollar_sign(char ***args);
void	init_ptr(char **envp);
void	handle_dollar_sign_3(char ***args);
void	add_back_list(char ***arr, char *str);
void	insert_wild(char **arr, char ***arg, int j);

#endif