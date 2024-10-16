/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallali <rallali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:02:44 by rallali           #+#    #+#             */
/*   Updated: 2024/09/30 01:04:23 by rallali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_env(char **copy_env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (copy_env[i])
	{
		j = 0;
		while (copy_env[i][j])
		{
			printf("%c", copy_env[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

char	**var_env(char **env)
{
	int		i;
	char	**copy_env;

	i = 0;
	copy_env = NULL;
	while (env[i])
		i++;
	copy_env = malloc ((i + 1) * sizeof (char *));
	if (!copy_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		copy_env[i] = strdup(env[i]);
		if (!copy_env[i])
		{
			while (--i >= 0)
				free (copy_env[i]);
			free (copy_env);
			return (NULL);
		}
		i++;
	}
	copy_env[i] = NULL;
	return (copy_env);
}
