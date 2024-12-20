/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 19:48:21 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/20 19:36:21 by ayhamdou         ###   ########.fr       */
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
	char		**splitted;
	t_token		*new;
	t_token		*tmp;
	int i;

	if ((*tokens)->token_type == WORD || (*tokens)->token_type == ENV)
	{
		if ((*tokens)->q_type == DOUBLE /*|| (*tokens)->q_type == NONE)*/)
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
		else
		{
			res = ft_strdup("");
			expand_it((*tokens)->str, &res, &expanded, ev);
			(*tokens)->has_expaned = 0;
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
	}
}

void remove_chars(char *str)
{
    int i = 0, j = 0;

    while (str[i] != '\0')
    {
        if (str[i] == '$' && (str[i + 1] == '\'' || str[i + 1] == '"'))
        {
            i++;
        }
        else
        {
            str[j] = str[i];
            j++;
        }
        i++;
    }
    str[j] = '\0';
}

void	expander(t_token **tokens, t_env *ev)
{
	t_token	*head;
	char	*res;
	int		is_exp;

	head = *tokens;
	while ((*tokens))
	{
		is_exp = 1;
		if ((*tokens)->prev)
		{
			if ((*tokens)->prev->token_type == HER)
				is_exp = 0;
			else
				is_exp = 1;
		}
		if (is_exp != 0)
		{
			if (!ft_strcmp((*tokens)->str, "~"))
			{
				res = ft_strdup("HOME");
				update_token(tokens, &res, ev);
			}
			handle_quoted_token(tokens, ev);
		}
		else
		{
			res = ft_strdup((*tokens)->str);
			remove_chars(res);
			(*tokens)->str = res;
		}
		(*tokens) = (*tokens)->next;
	}
	*tokens = head;
}
