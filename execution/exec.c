/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 04:08:26 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/22 04:08:44 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirct_it(t_redir *r)
{
	while (r)
	{
		red_dup(&r);
		r = r->next;
	}
}

void	ft_child_process(int prev_fd, int pipe_fd[2], t_command *cmd, t_env *ev)
{
	char		**env;
	t_redir		*r;
	int			status;

	status = 0;
	env = convert_ev(ev);
	if (prev_fd != -1)
		pipe_in(prev_fd);
	if (cmd->next)
		pipe_out(pipe_fd);
	if (cmd->is_builtin)
	{
		status = exec_builtin(cmd, ev);
		exit_status(status);
		exit(status);
	}
	else
	{
		r = cmd->rederects;
		redirct_it(r);
		if (execve(get_path(cmd, ev), cmd->args, env))
			status = errors(cmd->args[0], cmd);
		exit(status);
	}
}

void	pipe_manipulation(int *prev_fd, t_command *cmd, int pipe_fd[2])
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cmd->next)
	{
		close(pipe_fd[1]);
		*prev_fd = pipe_fd[0];
	}
	else
		*prev_fd = -1;
}

void	exec(t_command *commands, t_env *ev)
{
	int		prev_fd;
	int		status;

	prev_fd = -1;
	status = 0;
	if (!commands || !commands->args)
		return ;
	if (open_files(&commands, ev) == 1)
		return ;
	multiple_commands(commands, ev, &status, &prev_fd);
}
