#include "../minishell.h"

char	*get_path(t_command *command, t_env *env)
{
	char	*path;
	char	**paths;
	int		i;

	// if (access(command -> args[0], F_OK) == 0)
	// 	return (command -> args[0]);
	if (ft_strchr(command->args[0], '/'))
	{
		if (access(command->args[0], F_OK | X_OK) == 0)
			return (command->args[0]);
		else
			return (NULL);
	}
	path = ft_getenv(env, "PATH");
	paths = ft_split(path, ':');
	i = 0;
	while (paths[i])
	{
		if (paths[i][ft_strlen(paths[i]) - 1] != '/' )
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

// int red(char *path)
// {
//     struct stat    statbuf;

//     if ((stat(path, &statbuf) == 0)
//         && ((path[0] == '.' && path[1] == '/') || path[0] == '/'))
//     {
//         if (S_ISDIR(statbuf.st_mode))
//             return (1);
//         else if (S_ISREG(statbuf.st_mode))
//             return (2);
//     }
//     return (0);
// }

char **convert_ev(t_env *ev)
{
	char **env;
	int count = 0;
	t_env *temp = ev;
	char *t;

	while (temp)
	{
		count++;
		temp = temp->next;
	}
	env = ft_malloc(sizeof(char *) * (count + 1));
	if (!env)
		return (NULL);
	int i = 0;
	while (ev)
	{
		if (ev->key && ev->value)
		{
			t = ft_strjoin(ft_strdup(ev->key), "=");
			env[i] = ft_strjoin(t, ev->value);
		}
		else if (ev->key)
			env[i] = ft_strdup(ev->key);
		else
			env[i] = NULL;
		i++;
		ev = ev->next;
	}
	env[i] = NULL;
	return (env);
}

int	errors(char *str)
{
	struct stat    statbuf;	

	if (access(str, F_OK) == -1)
	{
		printf("minishell: %s: command not found\n", str);
		exit_status(127);
		exit(127);
	}
	else if (access(str, X_OK) == -1)
	{
		printf("minishell: %s: Permission denied\n", str);
		exit_status(126);
		exit(126);
	}
	if (stat(str, &statbuf) == -1)
	{
		printf("minishell: %s: No such file or directory\n", str);
		exit_status(127);
		exit(127);
	}
	else if (S_ISDIR(statbuf.st_mode))
	{
		printf("minishell: %s: is a directory\n", str);
		exit_status(126);
		exit(126);
	}
return (0);
}

void	ft_child_process(int prev_fd, int pipe_fd[2], t_command *cmd, t_env *ev)
{
	char	**env;
	t_redir	*r;
	int status = 0;

	env = convert_ev(ev);
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
	{
		status = exec_builtin(cmd, ev);
		exit_status(status);
		exit(status);
	}
	else
	{
		if (execve(get_path(cmd, ev), cmd->args, env))
			status = errors(cmd->args[0]);
		exit(status);
	}
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

void child_signal(void)
{
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, SIG_IGN);
}

void parent_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	multiple_commands(t_command *command, t_env *ev)
{
	int		prev_fd;
	int		pipe_fd[2];
	pid_t	last_pid;
	pid_t	pid;
	int status = 0;

	prev_fd = -1;
	last_pid = -1;

	if (command->is_builtin && !command->next)
	{
		status = exec_builtin(command, ev);
		exit_status(status);
		return;
	}
	else
	{
		while (command)
		{
			if (command->next && pipe(pipe_fd) == -1)
				put_err("pipe failed", 1);
			pid = fork();
			if (pid == 0)
			{
				child_signal();
				ft_child_process(prev_fd, pipe_fd, command, ev);
			}
			else if (pid < 0)
			{
				status = exit_status(1);
				break;
			}
			else
			{
				parent_signal();
				last_pid = pid;
			}
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
