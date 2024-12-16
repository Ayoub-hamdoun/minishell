/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helper_0.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:40:39 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/16 20:34:58 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_it(char *str, char **res, char **expanded, t_env *ev)
{
	char	tmp[2];
	int		i;
	char	*tmp_res;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && (ft_isalpha(str[i + 1]) || str[i + 1] == '_'))
		{
			i++;
			*expanded = ret_env(str, &i, ev);
			*res = ft_strjoin(*res, *expanded);
			//free(*expanded);
		}
		else if (str[i] == '$' && str[i + 1] == '?')
		{
			i += 2;
			tmp_res = ft_itoa(g_exit_status);
			*res = ft_strjoin(*res, tmp_res);
			//free(tmp_res);
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

int	has_quotes(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

void	update_token(t_token **token, char **res, t_env *ev)
{
	//free((*token)->str);
	(*token)->str = ft_strdup(ft_getenv(ev, *res));
	//free(*res);
}
