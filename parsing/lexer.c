/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:35:54 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/04 13:35:21 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_first_quote(t_token *token)
{
	if (!token)
		return (-1);
	if (token->str[0] == '\'')
		return (1);
	else if (token->str[0] == '"')
		return (2);
	return (0);
}

int	check_last_quote(t_token *token)
{
	int	i;

	if (!token || ft_strlen(token->str) == 1)
		return (-1);
	i = ft_strlen(token->str) - 1;
	if (token->str[i] == '\'')
		return (1);
	else if (token->str[i] == '"')
		return (2);
	return (0);
}

int	check_quotes(t_token *token)
{
	t_token	*current;
	int		checker;
	int		checker2;

	current = token;
	checker = 0;
	checker2 = 0;
	if (!current)
		return (1);
	while (current)
	{
		if (current ->str[0] == '\'' || current->str[0] == '"' )
		{
			checker = check_first_quote(current);
			checker2 = check_last_quote(current);
		}
		current = current->next;
	}
	if (checker != checker2 || checker == -1 || checker2 == -1)
	{
		printf("minishell: syntax error: mismatched quotes\n");
		return (1);
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
				printf(": in: No such file or directory\n");
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
	check_first_p(tmp);
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
