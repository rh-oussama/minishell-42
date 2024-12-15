/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 22:07:21 by oussama           #+#    #+#             */
/*   Updated: 2024/03/31 15:36:42 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execve(int parent, char *binary_path, char **args, int *pid)
{
	if (parent)
	{
		signal(SIGINT, ft_magic);
		*pid = fork();
		if (*pid == -1)
			return (ft_print_error("fork", "error\n", 1));
		if (*pid == 0)
		{
			if (execve(binary_path, args, g_ptr.envp) == -1)
				perror("execve");
			else
				perror(binary_path);
			exit(1);
		}
	}
	else
	{
		signal(SIGINT, ft_magic);
		if (execve(binary_path, args, g_ptr.envp) == -1)
			perror("execve");
		else
			perror(binary_path);
		exit(1);
	}
	return (0);
}

void	execute(char **args, int parent)
{
	int		pid;
	char	*binary_path;

	binary_path = get_final_path(args[0]);
	if (!binary_path || is_directory(binary_path) || access(binary_path, X_OK))
	{
		free(binary_path);
		check_file(args[0]);
		return ;
	}
	ft_execve(parent, binary_path, args, &pid);
	waitpid(pid, &g_ptr.pstatus, 0);
	if (WTERMSIG(g_ptr.pstatus) == 2)
		g_ptr.pstatus = 130;
	else
		g_ptr.pstatus = WEXITSTATUS(g_ptr.pstatus);
	free(binary_path);
}

void	build_in_functions(t_cmd *cmd, int parent)
{
	ft_underscore(cmd->args);
	if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		echo_handler(cmd->args);
	else if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		cd_handler(cmd->args);
	else if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		ft_print_cwd();
	else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		export_var(cmd->args);
	else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		unset_var(cmd->args);
	else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
	{
		if (!cmd->args[1])
			printf_env();
		else
		{
			g_ptr.pstatus = 1;
			ft_putendl_fd("env: Does not take arguments!", 2);
		}
	}
	else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		ft_exit(cmd->args);
	else if (cmd->args[0])
		execute(cmd->args, parent);
}

void	execute_command(t_cmd *cmd, int parent)
{
	t_fdbackup	backup;

	if (open_inredirections(cmd->in_red) || open_outredirections(cmd->out_red))
		return ;
	if (!cmd->args)
		return ;
	if (!cmd->args[0])
		return ;
	fdbackup(&backup);
	if (apply_redirections(cmd))
	{
		default_io(backup);
		return ;
	}
	handle_dollar_sign(&cmd->args);
	apply_wild_card(&cmd->args);
	handle_quots_value(cmd);
	build_in_functions(cmd, parent);
	default_io(backup);
}
