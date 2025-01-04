/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multiple_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 04:06:58 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/22 17:25:24 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_signal(void)
{
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, SIG_DFL);
}

void	parent_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_child(int prev_fd, int *pipe_fd, t_command *command, t_env *ev)
{
	child_signal();
	ft_child_process(prev_fd, pipe_fd, command, ev);
	close_red(command->rederects);
}

void	handle_fork_err(t_redir *r, int *status, int *pipe_fd)
{
	*status = exit_status(1);
	close_red(r);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

void	multiple_commands(t_command *command, t_env *ev,
		int *status, int *prev_fd)
{
	int		pipe_fd[2];
	pid_t	last_pid;
	pid_t	pid;

	last_pid = -1;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	if (command->is_builtin && !command->next)
		return (exec_the_builtin(command, ev, status));
	while (command)
	{
		create_pipe(&command, pipe_fd, &pid);
		if (pid == 0)
			handle_child (*prev_fd, pipe_fd, command, ev);
		else if (pid < 0)
		{
			handle_fork_err(command->rederects, status, pipe_fd);
			break ;
		}
		else
			close_reds(command->rederects, &last_pid, pid);
		loop_increment(&command, prev_fd, pipe_fd);
	}
	wait_for_all_processes(last_pid);
}
