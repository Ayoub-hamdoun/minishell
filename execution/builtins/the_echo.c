/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallali <rallali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:58:07 by rallali           #+#    #+#             */
/*   Updated: 2024/10/15 12:02:35 by rallali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_n(char *cmd)
{
	int	i;

	i = 1;
	if (cmd[0] == '-')
	{
		while (cmd[i] == 'n')
			i++;
		if (cmd[i] == '\0')
			return (0);
	}
	return (1);
}

void	the_echo(t_command *cmd)
{
	int	count;
	int	i;

	if (!cmd->args[1])
	{
		printf("\n");
		return ;
	}
	count = 0;
	i = 1;
	while (cmd->args[i] && count_n(cmd->args[i]) == 0)
	{
		count = 1;
		i++;
	}
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
	if (count == 0)
		printf("\n");
}
