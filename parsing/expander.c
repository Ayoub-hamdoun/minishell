/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 19:48:21 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/04 13:31:18 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_token(t_token **token, char **res, t_env *ev)
{
	free((*token)->str);
	(*token)->str = ft_strdup(ft_getenv(ev, *res));
	free(*res);
}

void	handle_env_token(t_token **tokens, t_env *ev)
{
	char	*res;

	if (!ft_strcmp((*tokens)->str, "$"))
		return ;
	res = ft_strdup(((*tokens)->str) + 1);
	if (ft_isalpha(res[0]) || res[0] == '_')
	{
		free((*tokens)->str);
		(*tokens)->str = ft_strdup(ft_getenv(ev, res));
		free(res);
	}
}

void	handle_quoted_token(t_token **tokens, t_env *ev)
{
	char	*str;
	char	*res;
	char	*expanded;

	if ((*tokens)->token_type == WORD && (*tokens)->q_type == DOUBLE)
	{
		str = ft_strdup((*tokens)->str);
		res = ft_strdup("");
		expand_it(str, &res, &expanded, ev);
		free((*tokens)->str);
		(*tokens)->str = ft_strdup(res);
		free(res);
		free(str);
	}
}

void	expander(t_token **tokens, t_env *ev)
{
	t_token	*head;
	char	*res;

	head = *tokens;
	while ((*tokens))
	{
		if ((*tokens)->token_type == ENV)
			handle_env_token(tokens, ev);
		else if (!ft_strcmp((*tokens)->str, "~"))
		{
			res = ft_strdup("HOME");
			update_token(tokens, &res, ev);
		}
		handle_quoted_token(tokens, ev);
		(*tokens) = (*tokens)->next;
	}
	*tokens = head;
}
