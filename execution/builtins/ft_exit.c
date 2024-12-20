/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 13:32:00 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/20 21:01:52 by ayhamdou         ###   ########.fr       */
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

long long	ft_atol(char *str, int *ovrd)
{
	int			i;
	long long	sign;
	long long	n;
	long long	tmp;

	i = 0;
	sign = 1;
	n = 0;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign = -sign;
		i++;
	}
	while (str[i] && str[i] >= 48 && str[i] <= 57)
	{
		tmp = n;
		n = n * 10 + str[i++] - 48;
		if (n < tmp)
			*ovrd = 1;
	}
	return (n * sign);
}

int	check_arg_num(t_command *command)
{
	int	i;

	i = 0;
	while (command->args[i])
		i++;
	if (i > 2)
		return (1);
	return(0);
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

int	ft_exit(t_command *command)
{
	int			i;
	long long	exitt;
	int			overf;

	i = 0;
	if (!command)
	{
		write(1, "exit\n", 5);
		exit(0);
	}
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
	{
		ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
		exit (255);
	}
	if (!command->args[1])
	{
		write(1, "exit\n", 5);
		exit (0);
	}
	else
	{
		write(1, "exit\n", 5);
		if (exitt < 0 || exitt > 255)
			exit (exitt % 256);
		exit (exitt);
	}
	return (0);
}
