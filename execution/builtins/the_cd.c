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
		if (strncmp (env->key, key, strlen (key)) == 0)
			return (env -> value);
		env = env -> next;
	}
	return (NULL);
}

char	*with_commands(t_command *cmd, char *need, t_env *env)
{
	if (cmd ->args[1])
	{
		if (cmd ->args[1][0] == '-')
		{
			need = get_need(env, "OLDPWD");
			printf("hu %s\n", need);
			if (need)
			{
				if (chdir(need) != 0)
					perror("chdir");
			}
			else
				printf("OLDPWD not set\n");
		}
		else if (chdir(cmd->args[1]) != 0)
			chdir("HOME");
	}
	return (need);
}

void	update_oldpwd(char *path, t_env *env)
{
	t_env *tmp = env;

	while (tmp)
	{
		if (ft_strcmp(tmp->key, "OLDPWD") == 0)
		{
			//free(tmp->value);
			tmp->value = ft_strdup(path);
			return;
		}
		tmp = tmp->next;
	}
}

void	update_pwd(char *pwd, t_env *env)
{
	t_env *tmp = env;

	while (tmp)
	{
		if (strcmp(tmp->key, "PWD") == 0)
		{
			//free(tmp->value);
			tmp->value = ft_strdup(pwd);
			return;
		}
		tmp = tmp->next;
	}
}

int	the_cd(t_command *cmd, t_env *env)
{
	char	*need;
	char	*oldpwd;
	char	*newpwd;
	int		chdir_result;

	oldpwd = getcwd(NULL, 0);
	free(oldpwd);
	if (!oldpwd)
		oldpwd = ft_strdup(get_need(env, "PWD"));

	if (!cmd->args[1] || !ft_strcmp(cmd->args[1], "~"))
	{
		need = get_need(env, "HOME");
		if (!need)
		{
			fprintf(stderr, "cd: HOME not set\n");
			return (1);
		}
		chdir_result = chdir(need);
	}
	else if (!ft_strcmp(cmd->args[1], "-"))
	{
		need = get_need(env, "OLDPWD");
		if (!need)
		{
			printf("cd: OLDPWD not set\n");
			return (1);
		}
		chdir_result = chdir(need);
		if (!chdir_result)
			printf("%s\n", need);
	}
	else
		chdir_result = chdir(cmd->args[1]);
	newpwd = getcwd(NULL, 0);
	free(newpwd);
	if (chdir_result || !newpwd)
	{
		perror("here :cd");
		if (!newpwd)
		{
			newpwd = ft_strjoin(ft_strdup(oldpwd), "/");
			if (cmd->args[1])
				newpwd = ft_strjoin(newpwd, cmd->args[1]);
			else
				newpwd = ft_strjoin(newpwd, "..");
		}
	}

	update_oldpwd(oldpwd, env);
	update_pwd(newpwd, env);
	return (0);
}
