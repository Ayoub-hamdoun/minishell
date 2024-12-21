/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files_helper_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 01:25:50 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/21 21:10:26 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	handle_here_sig(int sig)
{
	if (sig == SIGINT)
	{
		close(0);
		g_exit_status = SIGINT;
	}
	exit_status(-1);
}

void	handle_b_slash(int signal)
{
	(void)signal;
	rl_on_new_line();
	rl_redisplay();
}
