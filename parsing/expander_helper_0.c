/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helper_0.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:40:39 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/03 16:54:06 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_it(char *str, char **res, char **expanded, t_env *ev)
{
	char	tmp[2];
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && (ft_isalpha(str[i + 1]) || str[i + 1] == '_'))
		{
			i++;
			*expanded = ret_env(str, &i, ev);
			*res = ft_strjoin(*res, *expanded);
			free(*expanded);
		}
		else
		{
			tmp[0] = str[i];
			tmp[1] = '\0';
			*res = ft_strjoin(*res, tmp);
			i++;
		}
	}
}

char	*ret_env(char *str, int *i, t_env *ev)
{
	int		start;
	char	*env;
	char	*res;

	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	env = ft_substr(str, start, (*i) - start);
	res = ft_getenv(ev, env);
	if (res)
		return (ft_strdup(res));
	return (ft_strdup(""));
}
