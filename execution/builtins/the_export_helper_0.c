/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_export_helper_0.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 03:00:47 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/22 15:34:39 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	declare_x(t_env *env)
{
	while (env)
	{
		if (env->key && env->value)
			printf("declare_x %s=\"%s\"\n", env->key, env->value);
		else if (env->key && env->value == NULL)
			printf("declare_x %s\n", env->key);
		else if (env->key)
			printf("declare_x %s=\"\"\n", env->key);
		env = env->next;
	}
}

void	add_var(char *cmd, t_env **env, int append)
{
	char	*equal_pos;
	char	*key;
	char	*value;

	equal_pos = NULL;
	equal_pos = ft_strchr(cmd, '=');
	value = extract_value(equal_pos);
	key = extract_key(cmd, equal_pos);
	if (!update_var(env, key, value, append))
		add_new_var(env, key, value);
}

int	check_append(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '+' && cmd[i + 1] == '=')
			return (0);
		i++;
	}
	return (1);
}

int	check_on_env(t_env **env, char *key, char *value, int append)
{
	if (ft_strcmp((*env)->key, key) == 0)
	{
		if (!value)
			return (1);
		if (append == 0)
		{
			if (update_env_val(env, value))
				return (1);
		}
		else
		{
			free((*env)->value);
			(*env)->value = ft_strdup(value);
		}
		free(key);
		return (1);
	}
	return (0);
}

int	update_var(t_env **env, char *key, char *value, int append)
{
	t_env	*head;

	head = *env;
	while (*env)
	{
		if (check_on_env(env, key, value, append))
			return (1);
		(*env) = (*env)->next;
	}
	*env = head;
	return (0);
}
