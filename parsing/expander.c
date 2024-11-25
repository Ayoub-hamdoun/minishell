/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 19:48:21 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/11/25 20:38:36 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	has_env(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

void	rm_qt(char *str)
{
	char	*res;

	res = ft_substr(str, 1, ft_strlen(str) - 2);
	free(str);
	str = ft_strdup(res);
	free(res);
}

char	*ret_env(char *str, int *i)
{
	int start;
	char *env;

	start = *i;
	while (str[*i] && ft_isalnum(str[*i]))
		(*i)++;
	env = ft_substr(str, start, (*i) - start);
	if (getenv(env))
		return (ft_strdup(getenv(env)));
	return (ft_strdup(""));
}

void	expander(t_token **tokens)
{
	t_token *head;
	char	*str;
	char	*res;
	char	tmp[2];
	char	*expanded;
	int		i;

	head = *tokens;
	while ((*tokens))
	{
		if ((*tokens)->tokenType == ENV)
		{
			res = ft_strdup(((*tokens)->str) + 1);
			free((*tokens)->str);
			(*tokens)->str = ft_strdup(getenv(res));
			free(res);
		}
		else if (!ft_strcmp((*tokens)->str, "~"))
		{
			free((*tokens)->str);
			res = ft_strdup("HOME");
			(*tokens)->str = ft_strdup(getenv(res));
			free(res);
		}
		else if ((*tokens)->tokenType == WORD && (*tokens)->q_type == DOUBLE)
		{
			str = ft_strdup((*tokens)->str);
			rm_qt(str);
			res = ft_strdup("");
			i = 0;
			while (str[i])
			{
				if (str[i] == '$' && ft_isalpha(str[i + 1]))
				{
					i++;
					expanded = ret_env(str, &i);
					res = ft_strjoin(res, expanded);
					free(expanded);
				}
				else
				{
					tmp[0] = str[i];
					tmp[1] = '\0';
					res = ft_strjoin(res, tmp);
					i++;
				}
			}
			free((*tokens)->str);
			(*tokens)->str = ft_strdup(res);
			free(res);
			free(str);
		}
		(*tokens) = (*tokens)->next;
	}
	*tokens = head;
}
