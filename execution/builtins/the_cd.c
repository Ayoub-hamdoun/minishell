/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallali <rallali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:38:54 by rallali           #+#    #+#             */
/*   Updated: 2024/10/15 11:56:52 by rallali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			if (need)
			{
				if (chdir(need) != 0)
					perror("chdir");
			}
			else
				printf("OLDPWD not set\n");
		}
		else if (chdir(cmd->args[1]) != 0)
		{
			perror("chdir");
		}
	}
	return (need);
}

void	the_cd(t_command *cmd, t_env *env)
{
	char	*need;
	char	*path;

	need = NULL;
	need = with_commands(cmd, need, env);
	if (!cmd -> args[1])
	{
		need = get_need(env, "HOME");
		if (need)
		{
			if (chdir(need) != 0)
				perror("chdir");
		}
	}
	need = get_need(env, "PWD");
	update_oldpwd(need, env);
	path = getcwd(NULL, 0);
	re_pwd(path, env);
}
