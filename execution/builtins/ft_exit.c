/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 13:32:00 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/06 17:14:35 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exit(t_command *command)
{
	int	exit_status;
	int	i;

	i = 0;
	while (command->args[i])
		i++;
	exit_status = 0;
	if (i > 2)
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		return ;
	}
	if (!command->args[1])
	{
		write(1, "exit\n", 5);
		exit(0);
	}
	if (ft_isalpha(command->args[1][0]))
	{
		write(2, "minishell: exit: numeric argument required\n", 43);
		return ;
	}
	else
	{
		write(1, "exit\n", 5);
		exit_status = ft_atoi(command->args[1]);
		exit(exit_status);
	}
}
