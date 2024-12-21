/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 19:48:21 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/21 14:57:48 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	split_n_update(t_token **tokens, char **splitted)
{
	int		i;
	t_token	*tmp;
	t_token	*new;

	i = 1;
	(*tokens)->str = ft_strdup(splitted[0]);
	tmp = (*tokens);
	while (splitted[i])
	{
		new = ft_malloc(sizeof(t_token));
		new->str = ft_strdup(splitted[i]);
		new->token_type = WORD;
		new->q_type = NONE;
		new->next = tmp->next;
		new->prev = tmp;
		tmp->next = new;
		tmp = new;
		i++;
	}
}

void	handle_env_token(t_token **tokens, t_env *ev, char **expanded)
{
	char	*res;
	char	**splitted;

	res = ft_strdup("");
	expand_it((*tokens)->str, &res, expanded, ev);
	if (!ft_strcmp((*tokens)->str, res))
		(*tokens)->has_expaned = 0;
	else if (ft_strcmp((*tokens)->str, res) && !ft_strlen(res))
		(*tokens)->has_expaned = 1;
	else if (ft_strcmp((*tokens)->str, res) && ft_strlen(res))
		(*tokens)->has_expaned = 2;
	splitted = ft_split(res, ' ');
	if (!splitted || !sizeofarray(splitted))
		(*tokens)->str = ft_strdup("");
	else
		split_n_update(tokens, splitted);
}

void	handle_quoted_token(t_token **tokens, t_env *ev)
{
	char		*str;
	char		*res;
	char		*expanded;

	if ((*tokens)->token_type == WORD || (*tokens)->token_type == ENV)
	{
		if ((*tokens)->q_type != SINGLE)
		{
			if ((*tokens)->q_type == DOUBLE || has_tilda((*tokens)->str)
				|| ((*tokens)->q_type == NONE && (*tokens)->token_type != ENV))
			{
				str = ft_strdup((*tokens)->str);
				res = ft_strdup("");
				expand_it(str, &res, &expanded, ev);
				if (!ft_strcmp((*tokens)->str, res))
					(*tokens)->has_expaned = 0;
				else
					(*tokens)->has_expaned = 1;
				(*tokens)->str = ft_strdup(res);
			}
			else if ((*tokens)->token_type == ENV)
				handle_env_token(tokens, ev, &expanded);
		}
	}
}

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

void	expander(t_token **tokens, t_env *ev)
{
	t_token	*head;
	char	*res;
	int		is_exp;

	head = *tokens;
	while ((*tokens))
	{
		is_expandable(tokens, &is_exp);
		if (is_exp)
			handle_quoted_token(tokens, ev);
		else
		{
			res = remove_chars((*tokens)->str);
			(*tokens)->str = res;
		}
		(*tokens) = (*tokens)->next;
	}
	*tokens = head;
}
