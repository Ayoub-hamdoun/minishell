
// put your header here

#include "../minishell.h"

int	file_checkers(char	*file_name, t_etype file_type)
{
	if (file_type == R_IN)
	{
		if (check_file_in(file_name) == -1)
			return (1);
	}
	if (file_type == R_OUT)
	{
		if (check_file_out(file_name) == -1)
			return (1);
	}
	if (file_type == APP)
	{
		if (check_file_out(file_name) == -1)
			return (1);
	}
	return (0);
}
