
#include "../minishell.h"

void	wait_for_all_processes(pid_t	last_pid)
{
	int		status;
	pid_t	pid;
	int		exit_status;

	exit_status = 0;
	while (1)
	{
		pid = wait(&status);
		if (pid <= 0)
			break ;
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				exit_status = 128 + WTERMSIG(status);
		}
	}
	g_exit_status = exit_status;
}
