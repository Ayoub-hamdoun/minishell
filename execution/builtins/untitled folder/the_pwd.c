/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:38:21 by rallali           #+#    #+#             */
/*   Updated: 2024/12/07 19:28:18 by ayhamdou         ###   ########.fr       */
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

void	the_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		perror("pwd");
		return ;
	}
	printf("%s\n", path);
	free(path);
}
