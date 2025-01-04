/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 23:18:14 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/21 23:18:48 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_file_out(char *file_name)
{
	struct stat	filestat;

	if (access(file_name, R_OK) == -1)
	{
		printf("Error: permission denied '%s'.\n", file_name);
		exit_status(1);
		return (-1);
	}
	if (stat(file_name, &filestat) == -1)
	{
		perror("Error retrieving file info");
		exit_status(1);
		return (-1);
	}
	if (S_ISDIR(filestat.st_mode))
	{
		printf("Error: '%s' is a directory.\n", file_name);
		exit_status(1);
		return (-1);
	}
	return (0);
}

int	handle_input_redirection(t_command *cmd, t_redir **r)
{
	if ((*r)->type == R_IN && cmd->next && cmd->next->args)
	{
		if (file_checkers((*r)->filename, R_IN))
			(*r)->filename = "true";
		(*r)->fd = open((*r)->filename, O_RDONLY);
	}
	else if ((*r)->type == R_IN && (!cmd->next || !cmd->next->args))
	{
		if (file_checkers((*r)->filename, R_IN))
			return (1);
		(*r)->fd = open((*r)->filename, O_RDONLY);
		if ((*r)->fd == -1)
			return (1);
	}
	return (0);
}

int	handle_output_redirection(t_command *cmd, t_redir **r)
{
	if ((*r)->type == R_OUT && cmd->next && cmd->next->args)
	{
		(*r)->fd = open((*r)->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file_checkers((*r)->filename, R_OUT))
			(*r)->filename = "true";
	}
	else if ((*r)->type == R_OUT && (!cmd->next || !cmd->next->args))
	{
		(*r)->fd = open((*r)->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file_checkers((*r)->filename, R_OUT))
			return (1);
	}
	return (0);
}

int	handle_append_redirection(t_command *cmd, t_redir **r)
{
	if ((*r)->type == APP && cmd->next && cmd->next->args)
	{
		(*r)->fd = open((*r)->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (file_checkers((*r)->filename, APP))
			(*r)->filename = "true";
	}
	else if ((*r)->type == APP && (!cmd->next || !cmd->next->args))
	{
		(*r)->fd = open((*r)->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (file_checkers((*r)->filename, APP))
			return (1);
	}
	return (0);
}

int	open_files(t_command **commands, t_env *ev)
{
	t_command	*cmd;
	t_redir		*r;

	if (!*commands)
		return (1);
	cmd = *commands;
	while (cmd)
	{
		r = cmd->rederects;
		while (r)
		{
			if (open_it(cmd, &r, ev))
				return (1);
			r = r->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
