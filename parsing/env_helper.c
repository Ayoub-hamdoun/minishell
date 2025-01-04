/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 04:21:23 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/22 16:20:45 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	err_check(t_command **cmd)
{
	if ((*cmd)->args[1])
	{
		printf("minishell: No such file or directory\n");
		exit_status(127);
	}
}

int	print_env(t_command *cmd, t_env *env)
{
	int	fd;

	err_check(&cmd);
	fd = rederctes_out(cmd->rederects);
	while (env)
	{
		if (env->key && env->value)
		{
			write(fd, env->key, ft_strlen(env->key));
			if (ft_strcmp(env->key, "\0") != 0)
				write(fd, "=", 1);
			write(fd, env->value, ft_strlen(env->value));
			if (ft_strcmp(env->key, "\0") != 0)
				write(fd, "\n", 1);
		}
		env = env->next;
	}
	return (0);
}
