/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallali <rallali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:35:54 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/11/26 19:20:42 by rallali          ###   ########.fr       */
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
void check_quotes(int count_single, int count_double)
{
	if (count_single % 2 != 0)
	{
		printf("minishell: syntax error\n");
		exit(1);
	}
	else if (count_double % 2 != 0)
	{
		printf("minishell: syntax error\n");
		exit(1);
	}
}

void check_number_of_quotes(t_token *token)
{
	if (!token)
		return ;
	int i;
	int count_single;
	int count_double;
	i = 0;
	count_double = 0;
	count_single = 0;
	while (token)
	{
		i = 0;
		while (token->str[i])
		{
			if (token->str[i] == '\'')
				count_single++;
			else if (token->str[i] == '\"')
				count_double++;
			i++;
		}
		token = token->next;
	}
	check_quotes(count_single, count_double);
}

void lexer(t_token *tokens)
{
	t_token *tmp = tokens;

	while (tmp)
	{
		check_number_of_quotes(tmp);
		tmp  = tmp->next;
	}
}
