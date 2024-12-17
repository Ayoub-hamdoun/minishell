/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 19:48:21 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/17 15:43:05 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_env_token(t_token **tokens, t_env *ev)
{
	// (void)ev;
	char		*res;
	char		*expanded;
	char		**splitted;
	t_token		*new;
	t_token		*tmp;
	// t_token		*head;
	int			i;
	// int			j;
	// char		**splitted_str;
	// char	*str;
	// char	*res;
	// char	*expanded;

	// str = ft_strdup((*tokens)->str);
	// res = ft_strdup("");
	// expand_it(str, &res, &expanded, ev);
	// (*tokens)->str = ft_strdup(res);

	// printf("{{{{{{{%s}}}}}}}\n", (*tokens)->str);
	// splitted_str = ft_split((*tokens)->str, '$');
	// i = 1;
	// (*tokens)->str = ft_strdup(splitted_str[0]);
	// tmp = (*tokens);
	// while (splitted_str[i])
	// {
	// 	new = ft_malloc(sizeof(t_token));
	// 	new->str = ft_strdup(splitted_str[i]);
	// 	new->token_type = ENV;
	// 	new->q_type = NONE;
	// 	new->next = tmp->next;
	// 	new->prev = tmp;
	// 	tmp->next = new;
	// 	tmp = new;
	// 	i++;
	// }
	if (!ft_strcmp((*tokens)->str, "$"))
		return ;
	// res = ft_strdup(((*tokens)->str));
	// if (!ft_strcmp(res, "?"))
	// {
	// 	char *asc = ft_itoa(g_exit_status);
	// 	(*tokens)->str = ft_strdup(asc);
	// 	return ;
	// }
	// if (has_quotes(res))
	// {
	// 	(*tokens)->str = ft_strdup(res);
	// }
	res = ft_strdup("");
	expand_it((*tokens)->str, &res, &expanded, ev);
	i = 1;
	// if (ft_isalpha(res[1]) || res[0] == '_')
	// {
		// splitted = ft_split(ft_getenv(ev, res), ' ');
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
	// }
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
		(*tokens)->str = ft_strdup(res);
		//free(res);
		//free(str);
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
			if ((*tokens)->token_type == ENV)
				handle_env_token(tokens, ev);
			else if (!ft_strcmp((*tokens)->str, "~"))
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
