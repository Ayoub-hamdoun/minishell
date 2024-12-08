/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallali <rallali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:38:21 by rallali           #+#    #+#             */
/*   Updated: 2024/12/07 21:06:14 by rallali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_oldpwd(char *path, t_env *env)
{
	if (!path)
		return ;
	while (env)
	{
		if (strncmp(env->key, "OLDPWD", 3) == 0 && env -> value)
		{
			free(env->value);
			env->value = strdup(path);
			break ;
		}
		env = env->next;
	}
	return ;
}

void	re_pwd(char *path, t_env *env)
{
	if (!path)
		return ;
	while (env)
	{
		if (strncmp(env->key, "PWD", 3) == 0 && env->value)
		{
			free(env->value);
			env->value = strdup(path);
			break ;
		}
		env = env->next;
	}
	return ;
}
char  *get_pwd(t_env *env)
{
	if (!env)
		return (NULL);
	while (env)
	{
		if (strncmp(env->key, "PWD", 3) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
void	the_pwd(t_redir *reder, t_env *env)
{
	char	*path;
	int		fd;
	
	path = get_pwd(env);
	fd = rederctes_out(reder);
	write(fd, path, ft_strlen(path));
	write(fd, "\n", 1);
}
