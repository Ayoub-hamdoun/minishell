/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:35:54 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/16 21:01:05 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_quotes(t_token *token)
{
	t_token	*current;
	int		i;
	char	quote;

	current = token;
	if (!current)
		return (1);
	while (current)
	{
		i = 0;
		quote = 0;
		while (current->str[i])
		{
			if ((current->str[i] == '\'' || current->str[i] == '\"') && !quote)
				quote = current->str[i];
			else if (current->str[i] == quote)
				quote = 0;
			i++;
		}
		if (quote)
		{
			printf("minishell: syntax error: mismatched quotes\n");
			return (1);
		}
		current = current->next;
	}
	return (0);
}

int	check_redirection(t_token *token)
{
	if (!token)
		return (1);
	while (token)
	{
		if (token->token_type == R_IN || token->token_type == R_OUT
			|| token->token_type == APP || token->token_type == HER)
		{
			if (!token->next)
			{
				printf("minishell: syntax error: mismatched redirection\n");
				return (1);
			}
			else if (token->next->token_type != WORD && token -> next-> token_type != ENV)
			{
				printf("syntax error near unexpected token\n");
				return (1);
			}
		}
		token = token->next;
	}
	return (0);
}

int	lexer(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	if (check_first_p(tmp))
		return (1);
	while (tmp)
	{
		if (check_redirection(tmp))
			return (1);
		if (check_quotes(tmp))
			return (1);
		if (check_doubled_pipe(tmp))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
