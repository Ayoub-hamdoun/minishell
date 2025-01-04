/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands_helper_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 23:39:58 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/22 17:14:24 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	wait_for_all_processes(pid_t	last_pid)
{
	int		status;
	pid_t	pid;

	status = 0;
	while (1)
	{
		pid = waitpid(-1, &status, 0);
		if (pid <= 0)
			break ;
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				exit_status(WEXITSTATUS(status));
			else if (WIFSIGNALED(status))
			{
				if (128 + WTERMSIG(status) == 131)
					ft_putstr_fd("Quit: 3\n", 2);
				if (128 + WTERMSIG(status) == 130)
					ft_putstr_fd("\n", 2);
				exit_status(128 + WTERMSIG(status));
			}
		}
	}
}

void	permission_denied(void)
{
	ft_putstr_fd("minishell: permission denied\n", 2);
	exit_status(126);
	exit(126);
}

void	no_such_file_or_directory(void)
{
	ft_putstr_fd("minishell: No such file or directory\n", 2);
	exit_status(127);
	exit(127);
}

void	is_directory(void)
{
	ft_putstr_fd("minishell: is a directory\n", 2);
	exit_status(126);
	exit(126);
}

int	errors(char *str, t_command *cmd)
{
	struct stat	statbuf;

	if (cmd->flag == 1)
	{
		exit_status(0);
		exit(0);
	}
	else if (cmd->flag == 0 && ft_strlen(cmd->args[0]))
	{
		ft_putstr_fd("minishell: command not found\n", 2);
		exit_status(127);
		exit(127);
	}
	else if (cmd->flag == 2 || cmd->flag == 0)
	{
		if (access(str, F_OK) == -1)
			command_not_found();
		if (access(str, X_OK) == -1)
			permission_denied();
		if (stat(str, &statbuf) == -1)
			no_such_file_or_directory();
		else if (S_ISDIR(statbuf.st_mode))
			is_directory();
	}
	return (0);
}
