/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 19:48:21 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/14 17:46:37 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_env_token(t_token **tokens, t_env *ev)
{
	char		*res;
	char		**splitted;
	t_token		*new;
	t_token		*tmp;
	int			i;

	if (!ft_strcmp((*tokens)->str, "$"))
		return ;
	res = ft_strdup(((*tokens)->str) + 1);
	if (!ft_strcmp(res, "?"))
	{
		char *asc = ft_itoa(g_exit_status);
		free((*tokens)->str);
		(*tokens)->str = ft_strdup(asc);
		free(res);
		free(asc);
		return ;
	}
	i = 1;
	if (has_quotes(res))
	{
		free((*tokens)->str);
		(*tokens)->str = ft_strdup(res);
		free(res);
	}
	else if (ft_isalpha(res[0]) || res[0] == '_')
	{
		free((*tokens)->str);
		splitted = ft_split(ft_getenv(ev, res), ' ');
		if (!splitted || !sizeofarray(splitted))
			(*tokens)->str = ft_strdup("");
		else
		{
			(*tokens)->str = ft_strdup(splitted[0]);
			tmp = (*tokens);
			while (splitted[i])
			{
				new = malloc(sizeof(t_token));
				new->str = ft_strdup(splitted[i]);
				new->token_type = WORD;
				new->q_type = NONE;
				new->next = tmp->next;
				tmp->next = new;
				tmp = new;
				i++;
			}
		}
		free(res);
	}
	else
		free(res);
}

void	handle_quoted_token(t_token **tokens, t_env *ev)
{
	char	*str;
	char	*res;
	char	*expanded;

	if ((*tokens)->token_type == WORD || (*tokens)->q_type == DOUBLE)
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
