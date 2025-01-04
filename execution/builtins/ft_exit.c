/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 13:32:00 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/22 02:56:26 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	put_err(char *str, int exit_code)
{
	ft_putstr_fd(str, 2);
	exit(exit_code);
}

int	check_arg_num(t_command *command)
{
	int	i;

	i = 0;
	while (command->args[i])
		i++;
	if (i > 2)
		return (1);
	return (0);
}

int	check_arg_type(t_command *command)
{
	int	i;

	i = 0;
	while (command->args[1][i])
	{
		if (ft_isalpha(command->args[1][i]))
			return (1);
		i++;
	}
	return (0);
}

void	exit_it(int exitt)
{
	write(1, "exit\n", 5);
	if (exitt < 0 || exitt > 255)
		exit (exitt % 256);
	exit (exitt);
}

int	ft_exit(t_command *command)
{
	int			i;
	long long	exitt;
	int			overf;

	i = 0;
	if (!command || !command->args[1])
		put_err("exit\n", 0);
	if (check_arg_num(command))
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
		return (1);
	}
	overf = 0;
	if (command->args[1][0])
		exitt = ft_atol(command->args[1], &overf);
	else
		exitt = 0;
	if (check_arg_type(command) || overf)
		put_err("minishell: exit: numeric argument required\n", 255);
	else
		exit_it(exitt);
	return (0);
}
