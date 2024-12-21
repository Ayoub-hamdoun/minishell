/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:30:24 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/21 20:17:51 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	extract_normal_char(t_token **current, int *i, char **new_str)
{
	int 	start;
	char	*tmp;

	start = *i;
	while ((*current)->str[*i] && (*current)->str[*i] != '\'' && (*current)->str[*i] != '\"')
		(*i)++;
	tmp = ft_substr((*current)->str, start, (*i) - start);
	*new_str = ft_strjoin(*new_str, tmp);
}

void	update_it(t_token **current, char **new_str)
{
	int		i;
	int		start;
	char	*tmp;
	char	quote;

	i = 0;
	while ((*current)->str[i])
	{
		if ((*current)->str[i] == '\'' || (*current)->str[i] == '\"')
		{
			quote = (*current)->str[i];
			i++;
			start = i;
			while ((*current)->str[i] && (*current)->str[i] != quote)
				i++;
			tmp = ft_substr((*current)->str, start, i - start);
			*new_str = ft_strjoin(*new_str, tmp);
			if ((*current)->str[i] == quote)
				i++;
		}
		else
			extract_normal_char(current, &i, new_str);
	}
}

void	remove_quotes(t_token **tokens)
{
	t_token	*current;
	char	*new_str;

	current = *tokens;
	while (current)
	{
		if (current->q_type != NONE || current->token_type == ENV)
		{
			new_str = ft_strdup("");
			update_it(&current, &new_str);
			current->str = ft_strdup(new_str);
		}
		current = current->next;
	}
}
