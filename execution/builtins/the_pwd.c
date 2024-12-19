/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:38:21 by rallali           #+#    #+#             */
/*   Updated: 2024/12/19 17:16:33 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void	update_oldpwd(char *path, t_env *env)
// {
// 	if (!path)
// 		return ;
// 	while (env)
// 	{
// 		if (strncmp(env->key, "OLDPWD", 3) == 0 && env -> value)
// 		{
// 			free(env->value);
// 			env->value = strdup(path);
// 			break ;
// 		}
// 		env = env->next;
// 	}
// 	return ;
// }

void	re_pwd(char *path, t_env *env)
{
	if (!path)
		return ;
	while (env)
	{
		if (strncmp(env->key, "PWD", 3) == 0 && env->value)
		{
			//free(env->value);
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
int	the_pwd(t_redir *reder, t_env *env)
{
	char	*path;
	int		fd;

	(void)env;
	path = getcwd(NULL, 0);
	if (!path)
	{
		printf("minishell: pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
		return (1);
	}
	fd = rederctes_out(reder);
	write(fd, path, ft_strlen(path));
	write(fd, "\n", 1);
	add(path);
	return (0);
}
