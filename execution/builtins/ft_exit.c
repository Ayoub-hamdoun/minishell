/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 13:32:00 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/14 20:08:51 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	put_err(char *str, int is_exit)
{
	ft_putstr_fd(str, 2);
	if (!is_exit)
		return ;
	exit(EXIT_FAILURE);
}

void	ft_exit(t_command *command)
{
	int	exit_status;
	int	i;

	i = 0;
	while (command->args[i])
		i++;
	exit_status = 0;
	if (i > 2)
		put_err("minishell: exit: too many arguments\n", 0);
	if (!command->args[1])
	{
		write(1, "exit\n", 5);
		exit(0);
	}
	if (ft_isalpha(command->args[1][0]))
		put_err("minishell: exit: numeric argument required\n", 0);
	else
	{
		write(1, "exit\n", 5);
		exit_status = ft_atoi(command->args[1]);
		exit(exit_status);
	}
}


// TODO : exit code whwn a neative value passde to exit
// eg : exit -8 : exit code 248