/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:17:58 by rallali           #+#    #+#             */
/*   Updated: 2024/12/17 15:52:19 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	remove_env_var(t_env **env, const char *key)
{
	t_env	*current;
	t_env	*prev;
	t_env	*temp;

	current = *env;
	prev = NULL;

	while (current)
	{
		if (strcmp(current->key, key) == 0 && ft_strcmp(current->key, "_") != 0)
		{
			temp = current;
			if (prev)
				prev->next = current->next;
			else
				*env = current->next;
			current = current->next;
			continue;
		}
		prev = current;
		current = current->next;
	}
}


void	process_unset_args(t_command *cmd, t_env **env)
{
	int	i;

	i = 1;
	while (cmd -> args[i])
	{
		remove_env_var(env, cmd->args[i]);
		i++;
	}
}

int check_param(char *str)
{
	int i;

	i = 1;
	if (!ft_isalpha(str[0]) || str[i] != '_')
		return (1);
	while (str[i])
	{
		if (!ft_isalpha(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	the_unset(t_command *cmd, t_env **env)
{
	int flag;

	flag = check_param(cmd->args[1]);
	if (flag)
		return (flag);
	process_unset_args(cmd, env);
	return (0);
}
