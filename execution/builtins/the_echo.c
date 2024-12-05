/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:58:07 by rallali           #+#    #+#             */
/*   Updated: 2024/12/05 20:07:29 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
int rederctes_out(t_redir *reder)
{
	while (reder)
	{
		if (reder-> type == R_OUT)
		{
			if (reder -> flag_out)
				return (reder -> fd);
		}
		reder= reder -> next;
	}
	return(1);
}
void	the_echo(t_command *cmd)
{
	int	count;
	int	i;
	int fd;
	fd = rederctes_out(cmd -> rederects);
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
		// printf("%s", cmd->args[i]);
		write(fd,cmd -> args[i],strlen(cmd -> args[i]));
		if (cmd->args[i + 1])
			//printf(" ");
			write(fd," ",1);
		i++;
	}
	if (count == 0)
		write(fd,"\n",1);
		// printf("\n");
	// close(fd);
}
