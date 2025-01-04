/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_export_helper_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 03:03:32 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/22 16:18:33 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
				|| cmd[i] == '_' || cmd[i] == '='
				|| (cmd[i] == '+' && cmd[i + 1] == '=')))
		{
			return (1);
		}
		i++;
	}
	return (0);
}
