/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:25:30 by rallali           #+#    #+#             */
/*   Updated: 2024/10/16 16:33:55 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*extract_key(char *cmd, char *equal_pos)
{
	char	*plus_pos;

	plus_pos = strchr(cmd, '+');
	if (plus_pos && plus_pos < equal_pos)
		return (strndup(cmd, plus_pos - cmd));
	if (equal_pos)
		return (strndup(cmd, equal_pos - cmd));
	return (strdup(cmd));
}

char	*extract_value(char *equal_pos)
{
	if (equal_pos)
		return (strdup(equal_pos + 1));
	return (NULL);
}

int	update_var(t_env *env, char *key, char *value, int append)
{
	char	*new_value;

	while (env)
	{
		if (strcmp(env->key, key) == 0)
		{
			if (append == 0)
			{
				if (env->value)
				{
					new_value = malloc(strlen(env->value) + strlen(value) + 1);
					if (!new_value)
					{
						perror("Failed to allocate memory for value append");
						return (1);
					}
					strcpy(new_value, env->value);
					strcat(new_value, value);
					free(env->value);
					env->value = new_value;
				}
				else
					env->value = value;
			}
			else
			{
				free(env->value);
				env->value = value;
			}
			free(key);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

// int update_var(t_env *env, char *key, char *value)
// {
//     while (env) 
//     {
//         if (strcmp(env->key, key) == 0) 
//         {
//             free(env->value);
//             env->value = value;
//             free(key);
//             return 1;
//         }
//         env = env->next;
//     }
//     return 0;
// }
// int update_var(t_env *env, char *key, char *value)
// {
//     while (env) 
//     {
//         if (strcmp(env->key, key) == 0) 
//         {
//             free(env->value);
//             env->value = value;
//             free(key);
//             return 1;
//         }
//         env = env->next;
//     }
//     return 0;
// }

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

void	add_new_var(t_env **env, char *key, char *value)
{
	t_env	*new_var;
	t_env	*last;

	new_var = (t_env *) malloc(sizeof(t_env));
	if (!new_var)
	{
		perror("Failed to allocate memory");
		free(key);
		free(value);
		return ;
	}
	new_var->key = key;
	new_var->value = value;
	new_var->next = NULL;
	if (*env == NULL)
		*env = new_var;
	else
	{
		last = *env;
		while (last->next)
			last = last->next;
		last->next = new_var;
	}
}

void	add_var(char *cmd, t_env **env, int append)
{
	char	*equal_pos;
	char	*key;
	char	*value;

	value = extract_value(equal_pos);
	equal_pos = strchr(cmd, '=');
	key = extract_key(cmd, equal_pos);
	if (!update_var(*env, key, value, append))
		add_new_var(env, key, value);
}

int	check_equal(char *cmd)
{
	return (strchr(cmd, '=') == NULL);
}

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

int	check_valid(char *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if ((cmd[0] >= 'A' && cmd[0] <= 'Z')
		|| (cmd[0] >= 'a' && cmd[0] <= 'z') || cmd[0] == '_')
		j = 0;
	else
		return (1);
	while (cmd[i] != '=' && cmd[i])
	{
		if (!((cmd[i] >= 'A' && cmd[i] <= 'Z')
				|| (cmd[i] >= 'a' && cmd[i] <= 'z')
				|| (cmd[i] >= '0' && cmd[i] <= '9')
				|| cmd[i] == '_' || cmd[i] == '='))
		{
			if (cmd[i] == '+' && cmd[i + 1] == '=')
				i++;  // Skip '=' after '+'
			else
				return (1);
		}
		i++;
	}
	return (0);
}

void the_export(t_command *cmd, t_env **env)
{
	int	i;
	int	append;

	i = 1;
	if (!cmd->args[i])
	{
		declare_x(*env);
		return ;
	}
	while (cmd->args[i])
	{
		append = check_append(cmd->args[i]);
		if (check_valid(cmd->args[i]) == 0)
			add_var(cmd->args[i], env, append);
		else
			printf("export: `%s': not a valid identifier\n", cmd->args[i]);
		i++;
	}
}

