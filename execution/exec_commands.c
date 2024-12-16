#include "../minishell.h"

char	*get_path(t_command *command, t_env *env)
{
	char	*path;
	char	**paths;
	int		i;

	if (access(command -> args[0], F_OK) == 0)
		return (command -> args[0]);
	path = ft_getenv(env, "PATH");
	paths = ft_split(path, ':');
	i = 0;
	while (paths[i])
	{
		if (paths[i][ft_strlen(paths[i]) - 1] != '/')
		{
			paths[i] = ft_strjoin(paths[i], "/");
			paths[i] = ft_strjoin(paths[i], command -> args[0]);	
		}
		if (access(paths[i], F_OK) == 0)
		{
			command -> args[0] = paths[i];
			return (paths[i]);
		}
		i++;
	}
	return (NULL);
}

void	ft_child_process(int prev_fd, int pipe_fd[2], t_command *cmd, t_env *ev)
{
	char	**env;
	t_redir	*r;

	env = NULL;
	if (prev_fd != -1)
		pipe_in(prev_fd);
	if (cmd->next)
		pipe_out(pipe_fd);
	r = cmd->rederects;
	while (r)
	{
		red_dup(&r);
		r = r->next;
	}
	if (cmd->is_builtin)
		exec_builtin(cmd, ev);
	else
	{
		execve(get_path(cmd, ev), cmd->args, env);
		perror("execve failed");
		printf("%s: command not found\n", cmd->args[0]);
	}
	exit(EXIT_FAILURE);
}

void pipe_manipulation(int *prev_fd, t_command *cmd, int pipe_fd[2])
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

void	multiple_commands(t_command *command, t_env *ev)
{
	int		prev_fd;
	int		pipe_fd[2];
	pid_t	last_pid;
	pid_t	pid;

	prev_fd = -1;
	last_pid = -1;
	if (command->is_builtin && !command->next)
		exec_builtin(command, ev);
	else
	{
		while (command)
		{
			if (command->next && pipe(pipe_fd) == -1)
				put_err("pipe failed", 1);
			pid = fork();
			if (pid == 0)
				ft_child_process(prev_fd, pipe_fd, command, ev);
			else if (pid < 0)
				put_err("fork failed", 1);
			else
				last_pid = pid;
			pipe_manipulation(&prev_fd, command, pipe_fd);
			close_red(command -> rederects);
			command = command->next;
		}
	}
	wait_for_all_processes(last_pid);
}

void	exec(t_command *commands, t_env *ev)
{
	if (!commands || !commands->args)
		return ;
	if (open_files(&commands, ev) == 1)
		return ;
	multiple_commands(commands, ev);
}
