/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 04:05:44 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/22 04:37:01 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_the_builtin(t_command *command, t_env *ev, int *status)
{
	*status = exec_builtin(command, ev);
	close_red(command->rederects);
	exit_status(*status);
	return ;
}

void	close_reds(t_redir *r, int *last_pid, pid_t pid)
{
	parent_signal();
	close_red(r);
	*last_pid = pid;
}

void	create_pipe(t_command **command, int *pipe_fd, pid_t *pid)
{
	if ((*command)->next && pipe(pipe_fd) == -1)
		put_err("pipe failed", 1);
	*pid = fork();
}

void	loop_increment(t_command **command, int *prev_fd, int *pipe_fd)
{
	pipe_manipulation(prev_fd, *command, pipe_fd);
	(*command) = (*command)->next;
}
