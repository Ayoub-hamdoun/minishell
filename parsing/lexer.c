/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallali <rallali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:35:54 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/01 17:50:16 by rallali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// i check here if the number of quotes is even or not 
//!!!!!!big warning you don t need to make it here tho but this function will help tho
//cases needed to be hanlded
//{
		//	"'"'"even tho the count is even it should return command error i dunno the cases tho but there is some cases that
		//the "'" is considered as a word and not a quote maybe we should handle it in the tokenizer
//}

// int check_first(t_token *token)
// {
// 	int i;

// 	i = 0;
// 	while (token->str[i] )
// 	{
// 		if (token->str[i] == '\'')
// 			return (i);
// 		else if (token->str[i] == '"')
// 			return (i);
// 		i++;
// 	}
// return (-1);
// }
// int check_last(t_token *token)
// {
// 	int i;

// 	i = ft_strlen(token->str) - 1;
// 	while (i >= 0)
// 	{
// 		if (token->str[i] == '\'')
// 			return (i);
// 		else if (token->str[i] == '"')
// 			return (i);
// 		i--;
// 	}
// 	return (-1);
// }

// void check_first_last(t_token *token)
// {
// 	int first;
// 	int last;

// 	first = check_first(token);
// 	last = check_last(token);
// 	if (first != -1 && last != -1)
// 	{
// 		if (first == 0 && last == ft_strlen(token->str) - 1)
// 		{
// 			if (token->str[first] == token->str[last])
// 			{
// 				printf("minishell: syntax error: mismatched quotes\n");
// 				exit(1);
// 			}
// 		}
// 	}
// }
// void check_quotes_alt(t_token *token) 
// {
// 	int total_single = 0;
// 	int total_double = 0;
// 	t_token *current = token;
// 	if (!current)
// 		return ;
// 	while (current) 
// 	{
// 		int i = 0;
// 		while (current->str[i]) 
// 		{
// 			if (current->str[i] == '\'')
// 				total_single++;
// 			if (current->str[i] == '"')
// 				total_double++;
// 			i++;
// 		}
// 		current = current->next;
// 	}
	
// 	if (total_single % 2 != 0 || total_double % 2 != 0) 
// 	{
// 		printf(">\n");
// 		exit(1);
// 	}
// }

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
	if (!token)
		return (-1);
	int i = ft_strlen(token->str) - 1;
	if (token->str[i] == '\'')
		return (1);
	else if (token->str[i] == '"')
		return (2);
	return (0);
}
void check_quotes(t_token *token)
{
	t_token *current = token;
	// int i = 0;
	int checker = 0;
	int checker2 = 0;
	if (!current)
		return ;
	while (current)
	{
		if (current ->str[0] == '\'' || current->str[0] == '"' )
		{
			checker = check_first_quote(current);
			checker2 = check_last_quote(current);
		}
		else if (current->str[ft_strlen(current->str) - 1] == '\'' || current->str[ft_strlen(current->str) - 1] == '"')
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
		if (current->tokenType == PIPE)
		{
			if (!current->next)
			{
				printf("> nothing after pipe\n");
				exit(1);
			}
			else if (current->next->tokenType == PIPE)
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
		if (token->tokenType == R_IN || token->tokenType == R_OUT || token->tokenType == APP || token->tokenType == HER)
		{
			if (!token->next)
			{
				printf("minishell: syntax error: mismatched redirection\n");
				exit(1);
			}
			else if (token->next->tokenType != WORD)
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
