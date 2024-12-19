/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 19:48:21 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/19 20:32:22 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_env_token(t_token **tokens, t_env *ev)
{
	char		*res;
	char		*expanded;
	char		**splitted;
	t_token		*new;
	t_token		*tmp;
	int			i;

	if (!ft_strcmp((*tokens)->str, "$"))
		return ;
	res = ft_strdup("");
	expand_it((*tokens)->str, &res, &expanded, ev);
	i = 1;
	splitted = ft_split(res, ' ');
	if (!splitted || !sizeofarray(splitted))
		(*tokens)->str = ft_strdup("");
	else
	{
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
}

void	handle_quoted_token(t_token **tokens, t_env *ev)
{
	char	*str;
	char	*res;
	char	*expanded;

	if ((*tokens)->token_type == WORD || (*tokens)->token_type == ENV)
	{
		if (((*tokens)->q_type == DOUBLE || (*tokens)->q_type == NONE))
		{
			str = ft_strdup((*tokens)->str);
			res = ft_strdup("");
			expand_it(str, &res, &expanded, ev);
			(*tokens)->str = ft_strdup(res);
		}
	}
}

void	expander(t_token **tokens, t_env *ev)
{
	t_token	*head;
	char	*res;
	int		is_exp;

	head = *tokens;
	is_exp = 1;
	while ((*tokens))
	{
		if ((*tokens)->prev)
		{
			if ((*tokens)->prev->token_type == HER)
				is_exp = 0;
			else
				is_exp = 1;
		}
		if (is_exp)
		{
			if (!ft_strcmp((*tokens)->str, "~"))
			{
				res = ft_strdup("HOME");
				update_token(tokens, &res, ev);
			}
			handle_quoted_token(tokens, ev);
		}
		(*tokens) = (*tokens)->next;
	}
	*tokens = head;
}
