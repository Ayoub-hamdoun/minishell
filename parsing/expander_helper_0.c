/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helper_0.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:40:39 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/21 01:47:56 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	join_char(char **res, int *i, char c)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	*res = ft_strjoin(*res, tmp);
	(*i)++;
}

void	join_home(char **res, char **expanded, int *i, t_env *ev)
{
	*expanded = ft_strdup(ft_getenv(ev, "HOME"));
	*res = ft_strjoin(*res, *expanded);
	(*i)++;
}

void	expand_it(char *str, char **res, char **expanded, t_env *ev)
{
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
		}
		else if (str[i] == '$' && str[i + 1] == '?')
		{
			i += 2;
			tmp_res = ft_itoa(exit_status(-1));
			*res = ft_strjoin(*res, tmp_res);
		}
		else if (str[i] == '~')
			join_home(res, expanded, &i, ev);
		else
			join_char(res, &i, str[i]);
	}
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
	(*token)->str = ft_strdup(ft_getenv(ev, *res));
	(*token)->has_expaned = 1;
}
