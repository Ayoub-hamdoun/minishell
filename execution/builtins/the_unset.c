/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallali <rallali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:17:58 by rallali           #+#    #+#             */
/*   Updated: 2024/12/13 21:15:54 by rallali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	remove_env_var(t_env **env, const char *key)
{
	t_env	*current;
	t_env	*prev;

	current = *env;
	prev = NULL;
	while (current)
	{
		if (strcmp(current->key, key) == 0)
		{
			free(current->key);
			free(current->value);
			if (prev)
				prev->next = current->next;
			else
				*env = current->next;
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	process_unset_args(t_command *cmd, t_env **env)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		remove_env_var(env, cmd->args[i]);
		i++;
	}
}

void	the_unset(t_command *cmd, t_env **env)
{
	process_unset_args(cmd, env);
}
