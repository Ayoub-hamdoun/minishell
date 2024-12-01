/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 23:23:02 by rallali           #+#    #+#             */
/*   Updated: 2024/12/01 19:33:30 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	with_or_without_sign(t_env *env, char **ev, int i, char *sign)
{
	if (!sign)
	{
		env->key = ft_strdup(ev[i]);
		env->value = NULL;
	}
	else
	{
		env->key = strndup(ev[i], sign - ev[i]);
		env->value = ft_strdup(sign + 1);
	}
}

char *get_line(t_env *env,char *key)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(env->key, key))
			return(env->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_getenv(t_env *env, char **ev)
{
	char	*sign;
	int		i;

	i = 0;
	if (!env || !*ev)
		return ;
	while (ev[i])
	{
		sign = strchr(ev[i], '=');
		with_or_without_sign(env, ev, i, sign);
		if (ev[i + 1])
		{
			env->next = malloc(sizeof(t_env));
			if (!env->next)
				return ;
			env = env->next;
		}
		else
			env->next = NULL;
		i++;
	}
}
