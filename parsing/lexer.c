/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:35:54 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/02 14:31:17 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_first_quote(t_token *token)
{
	if (!token)
		return (-1);
	if (token->str[0] == '\'')
		return (1);
	else if (token->str[0] == '"')
		return (2);
	return (0);
}
int check_last_quote(t_token *token)
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

void	check_quotes(t_token *token)
{
	t_token	*current;
	int		checker;
	int		checker2;

	current = token;
	checker = 0;
	checker2 = 0;
	if (!current)
		return ;
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
		exit(1);
	}
	return ;
}

void check_first_p(t_token *token)
{
	t_token *current = token;
	int i = 0;
	if (!current)
		return ;
	while (current -> str[i])
	{
		if (current->str[0] == '|')
		{
			{
				printf("minishell: syntax error: mismatched pipes\n");
				exit(1);
			}
		}
		i++;
	}
}
void check_doubled_pipe(t_token *token)
{
	t_token *current = token;
	if (!current)
		return ;
	while (current)
	{
		if (current->token_type == PIPE)
		{
			if (!current->next)
			{
				printf("> nothing after pipe\n");
				exit(1);
			}
			else if (current->next->token_type == PIPE)
			{
				printf("minishell: syntax error: mismatched pipes\n");
				exit(1);
			}
		}
		current = current->next;
	}
}
void check_redirection(t_token *token)
{
	if (!token)
		return ;

	while (token)
	{
		if (token->token_type == R_IN || token->token_type == R_OUT || token->token_type == APP || token->token_type == HER)
		{
			if (!token->next)
			{
				printf("minishell: syntax error: mismatched redirection\n");
				exit(1);
			}
			else if (token->next->token_type != WORD)
			{
				printf(": in: No such file or directory");
				exit(1);
			}
		}
		token = token->next;
	}
}
void lexer(t_token *tokens)
{
	t_token *tmp = tokens;

	check_first_p(tmp);
	while (tmp)
	{
		check_redirection(tmp);
		check_quotes(tmp);
		check_doubled_pipe(tmp);
		tmp  = tmp->next;
	}
}
