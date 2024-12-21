/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallali <rallali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:38:54 by rallali           #+#    #+#             */
/*   Updated: 2024/12/07 21:56:59 by rallali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_need(t_env *env, char *key)
{
	if (!key)
		return (NULL);
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	update_env_var(t_env *env, char *key, char *value)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			if (value)
				tmp->value = ft_strdup(value);
			else
				tmp->value = NULL;
			return ;
		}
		tmp = tmp->next;
	}
}

int	target_dire(t_command *cmd, t_env *env, char **oldpwd, char **target_dir)
{
	if (!*oldpwd)
		*oldpwd = ft_strdup(get_need(env, "PWD"));
	if (!cmd->args[1] || ft_strcmp(cmd->args[1], "~") == 0)
	{
		*target_dir = get_need(env, "HOME");
		if (!*target_dir)
		{
			printf("cd: HOME not set\n");
			return (free(*oldpwd), 1);
		}
	}
	else if (ft_strcmp(cmd->args[1], "-") == 0)
	{
		*target_dir = get_need(env, "OLDPWD");
		if (!*target_dir)
		{
			printf("cd: OLDPWD not set\n");
			return (free(*oldpwd), 1);
		}
		printf("%s\n", *target_dir);
	}
	else
		*target_dir = cmd->args[1];
	return (0);
}

int	the_cd(t_command *cmd, t_env *env)
{
	char	*oldpwd;
	char	*target_dir;
	char	*newpwd;

	oldpwd = getcwd(NULL, 0);
	target_dir = NULL;
	newpwd = NULL;
	if (target_dire(cmd, env, &oldpwd, &target_dir) != 0)
		return (1);
	if (chdir(target_dir) != 0)
	{
		perror("cd");
		return (free(oldpwd), 1);
	}
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
	{
		newpwd = ft_strjoin(oldpwd, "/");
		newpwd = ft_strjoin(newpwd, cmd->args[1]);
	}
	update_env_var(env, "OLDPWD", oldpwd);
	update_env_var(env, "PWD", newpwd);
	free(oldpwd);
	free(newpwd);
	return (0);
}
