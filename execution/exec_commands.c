/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 01:24:30 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/22 04:10:37 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_path(t_command *command, char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		if (paths[i][ft_strlen(paths[i]) - 1] != '/' )
		{
			paths[i] = ft_strjoin(paths[i], "/");
			paths[i] = ft_strjoin(paths[i], command -> args[0]);
		}
		if (access(paths[i], F_OK) == 0)
		{
			command -> args[0] = paths[i];
			return (paths[i]);
		}
		i++;
	}
	return (NULL);
}

char	*get_path(t_command *command, t_env *env)
{
	char	*path;
	char	**paths;
	char	*to_return;

	if (access(command->args[0], F_OK) == 0)
		return (command->args[0]);
	if (ft_strchr(command->args[0], '/'))
	{
		if (access(command->args[0], F_OK | X_OK) == 0)
			return (command->args[0]);
		else
			return (NULL);
	}
	path = ft_getenv(env, "PATH");
	paths = ft_split(path, ':');
	to_return = check_path(command, paths);
	if (to_return != NULL)
		return (to_return);
	return (NULL);
}

char	*create_env_var(char *key, char *value)
{
	char	*env_var;
	char	*t;

	if (key && value)
	{
		t = ft_strjoin(ft_strdup(key), "=");
		env_var = ft_strjoin(t, value);
		free(t);
	}
	else if (key)
	{
		env_var = ft_strdup(key);
	}
	else
	{
		env_var = NULL;
	}
	return (env_var);
}

char	**convert_ev(t_env *ev)
{
	char	**env;
	int		count;
	t_env	*temp;
	int		i;

	count = 0;
	temp = ev;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	env = ft_malloc(sizeof(char *) * (count + 1));
	if (!env)
		return (NULL);
	i = 0;
	while (ev)
	{
		env[i] = create_env_var(ev->key, ev->value);
		i++;
		ev = ev->next;
	}
	env[i] = NULL;
	return (env);
}

void	command_not_found(void)
{
	ft_putstr_fd("minishell: command not found\n", 2);
	exit_status(127);
	exit(127);
}
