/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 19:48:21 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/02 21:14:07 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ret_env(char *str, int *i)
{
	int start;
	char *env;
	char *res;

	start = *i;
	while (str[*i] && ft_isalnum(str[*i]))
		(*i)++;
	env = ft_substr(str, start, (*i) - start);
	res = getenv(env);
	if (res)
		return (ft_strdup(res));
	return (ft_strdup(""));
}

void	update_token(t_token **token, char **res)
{
	free((*token)->str);
	(*token)->str = ft_strdup(getenv(*res));
	free(*res);
}

void	handle_env_token(t_token **tokens)
{
	char	*res;

	res = ft_strdup(((*tokens)->str) + 1);
	if (ft_isalpha(res[0]) || res[0] == '_')
	{
		free((*tokens)->str);
		(*tokens)->str = ft_strdup(getenv(res));
		free(res);
	}
}

void	expand_it(char *str, char **res, char **expanded, int *i)
{
	char	tmp[2];

	while (str[*i])
	{
		if (str[*i] == '$' && (ft_isalpha(str[*i + 1]) || str[*i + 1] == '_'))
		{
			(*i)++;
			*expanded = ret_env(str, i);
			*res = ft_strjoin(*res, *expanded);
			free(*expanded);
		}
		else
		{
			tmp[0] = str[*i];
			tmp[1] = '\0';
			*res = ft_strjoin(*res, tmp);
			(*i)++;
		}
	}
}

void	handle_quoted_token(t_token **tokens)
{
	char	*str;
	char	*res;
	int		i;
	char	*expanded;

	i = 0;
	if ((*tokens)->token_type == WORD && (*tokens)->q_type == DOUBLE)
	{
		str = ft_strdup((*tokens)->str);
		res = ft_strdup("");
		expand_it(str, &res, &expanded, &i);
		free((*tokens)->str);
		(*tokens)->str = ft_strdup(res);
		free(res);
		free(str);
	}
}

void	expander(t_token **tokens)
{
	t_token *head;
	// char	*str;
	char	*res;
	// char	*expanded;

	head = *tokens;
	while ((*tokens))
	{
		if ((*tokens)->token_type == ENV)
			handle_env_token(tokens);
		else if (!ft_strcmp((*tokens)->str, "~"))
		{
			res = ft_strdup("HOME");
			update_token(tokens, &res);
		}
		handle_quoted_token(tokens);
		(*tokens) = (*tokens)->next;
	}
	*tokens = head;
}
