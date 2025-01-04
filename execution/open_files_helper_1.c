/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files_helper_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 01:25:50 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/22 03:14:09 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	file_checkers(char	*file_name, t_etype file_type)
{
	if (file_type == R_IN)
	{
		if (check_file_in(file_name) == -1)
			return (1);
	}
	if (file_type == R_OUT)
	{
		if (check_file_out(file_name) == -1)
			return (1);
	}
	if (file_type == APP)
	{
		if (check_file_out(file_name) == -1)
			return (1);
	}
	return (0);
}

void	handle_here_sig(int sig)
{
	if (sig == SIGINT)
	{
		close(0);
		g_exit_status = SIGINT;
	}
	exit_status(-1);
}

void	handle_b_slash(int signal)
{
	(void)signal;
	rl_on_new_line();
	rl_redisplay();
}

int	check_file_in(char *file_name)
{
	struct stat	filestat;

	if (access(file_name, F_OK) == -1)
	{
		perror("Error accessing file");
		exit_status (1);
		return (-1);
	}
	if (access(file_name, R_OK) == -1)
	{
		printf("Error: permission denied '%s'.\n", file_name);
		return (exit_status(1), -1);
	}
	if (stat(file_name, &filestat) == -1)
	{
		perror("Error retrieving file info");
		return (exit_status(1), -1);
	}
	if (S_ISDIR(filestat.st_mode))
	{
		printf("Error: '%s' is a directory.\n", file_name);
		exit_status(1);
		return (-1);
	}
	return (0);
}

int	open_it(t_command *cmd, t_redir **r, t_env *ev)
{
	if ((*r)->type == R_IN || (*r)->type == R_OUT
		|| (*r)->type == APP || (*r)-> type == HER)
	{
		if ((*r)->type == HER)
		{
			if (!cmd -> args[0])
				cmd -> args[0] = "true";
			check_on_herdoc((*r), ev);
		}
		else if ((*r)->type == R_IN)
			return (handle_input_redirection(cmd, r));
		else if ((*r)->type == R_OUT)
			return (handle_output_redirection(cmd, r));
		else if ((*r)->type == APP)
			return (handle_append_redirection(cmd, r));
	}
	return (0);
}
