
#include "../minishell.h"

void	wait_for_all_processes(void)
{
	int	status;

	while (1)
	{
		status = wait(NULL);
		if (status <= 0)
			break ;
	}
}
