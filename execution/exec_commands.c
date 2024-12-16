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

int red(char *path)
{
    struct stat    statbuf;

    if ((stat(path, &statbuf) == 0)
        && ((path[0] == '.' && path[1] == '/') || path[0] == '/'))
    {
        if (S_ISDIR(statbuf.st_mode))
            return (1);
        else if (S_ISREG(statbuf.st_mode))
            return (2);
    }
    return (0);
}

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

void    errors(char *str,char *path)
{
    int    is_red;

    if (!str)
        return ;
    is_red = red(path);
    ft_putstr_fd("minishell: ", STDERR_FILENO);
    ft_putstr_fd(str, STDERR_FILENO);
    if (is_red == 1)
        ft_putstr_fd(": is a directory\n", STDERR_FILENO);
    else if (is_red == 2)
        ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
    else
        ft_putstr_fd(": command not found\n", STDERR_FILENO);
    if (is_red)
        exit(126);
    exit(127);
}

void	ft_child_process(int prev_fd, int pipe_fd[2], t_command *cmd, t_env *ev)
{
	char	**env;
	t_redir	*r;

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
		exec_builtin(cmd, ev);
	else
	{
		execve(get_path(cmd, ev), cmd->args, env);
		errors(cmd->args[0], get_path(cmd, ev));
		// perror("execve failed");
		// printf("%s: command not found\n", cmd->args[0]);
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
			{
				child_signal();
				ft_child_process(prev_fd, pipe_fd, command, ev);
			}
			else if (pid < 0)
				put_err("fork failed", 1);
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
