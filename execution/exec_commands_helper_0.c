
#include "../minishell.h"

void	exec_builtin(t_command *command,t_env *ev)
{
	if (!command)
		return ;
	if (!ft_strcmp(command->args[0], "echo"))
		the_echo(command);
	else if (!ft_strcmp(command -> args[0], "cd"))
		the_cd(command, ev);
	else if (!ft_strcmp(command -> args[0], "pwd")
		|| !ft_strcmp(command -> args[0], "PWD"))
		the_pwd(command -> rederects, ev);
	else if (!ft_strcmp(command -> args[0], "export"))
		the_export(command, &ev);
	else if (!ft_strcmp(command -> args[0], "unset"))
		the_unset(command, &ev);
	else if (!ft_strcmp(command -> args[0], "env")
		|| !ft_strcmp(command -> args[0], "ENV"))
		print_env(command, ev);
	else if (!ft_strcmp(command->args[0], "exit"))
		ft_exit(command);
}

void	red_dup(t_redir **r)
{
	if ((*r)->type == R_IN || (*r)->type == HER)
		dup2((*r)->fd, STDIN_FILENO);
	else if ((*r)->type == R_OUT || (*r)->type == APP)
		dup2((*r)->fd, STDOUT_FILENO);
	close((*r)->fd);
}

void	pipe_in(int prev_fd)
{
	if (dup2(prev_fd, STDIN_FILENO) == -1)
		put_err("dup2 failed for input", 1);
	close(prev_fd);
}

void	pipe_out(int pipe_fd[2])
{
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		put_err("dup2 failed for output", 1);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
}

void	close_red(t_redir *r)
{
	while (r)
	{
		close(r->fd);
		r = r->next;
	}
}
