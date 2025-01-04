/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:25:30 by rallali           #+#    #+#             */
/*   Updated: 2024/12/22 16:20:55 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*extract_key(char *cmd, char *equal_pos)
{
	char	*plus_pos;

	plus_pos = ft_strchr(cmd, '+');
	if (plus_pos && plus_pos < equal_pos)
		return (ft_strndup(cmd, plus_pos - cmd));
	if (equal_pos)
		return (ft_strndup(cmd, equal_pos - cmd));
	return (ft_strdup(cmd));
}

char	*extract_value(char *equal_pos)
{
	if (equal_pos)
		return (ft_strdup(equal_pos + 1));
	return (NULL);
}

int	update_env_val(t_env **env, char *value)
{
	char	*new_value;
	char	*temp;

	if ((*env)->value)
	{
		new_value = ft_malloc(ft_strlen((*env)->value) + ft_strlen(value) + 1);
		if (!new_value)
		{
			perror("Failed to allocate memory for value append");
			return (1);
		}
		temp = ft_strcpy((*env)->value);
		ft_strcat(new_value, temp);
		ft_strcat(new_value, value);
		free(temp);
		free((*env)->value);
		(*env)->value = new_value;
	}
	else
		(*env)->value = ft_strcpy(value);
	return (0);
}

int	the_export(t_command *cmd, t_env **env)
{
	int	i;
	int	append;
	int	status;

	status = 0;
	i = 1;
	if (!cmd->args[i])
	{
		declare_x(*env);
		return (0);
	}
	while (cmd->args[i])
	{
		append = check_append(cmd->args[i]);
		if (check_valid(cmd->args[i]) == 0)
			add_var(cmd->args[i], env, append);
		else
		{
			printf("export: `%s': not a valid identifier\n", cmd->args[i]);
			status = 1;
		}
		i++;
	}
	return (status);
}
