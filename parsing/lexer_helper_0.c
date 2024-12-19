/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper_0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallali <rallali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:35:16 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/19 20:09:25 by rallali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_first_p(t_token *token)
{
	t_token	*current;
	int		i;

	current = token;
	i = 0;
	if (!current)
		return (1);
	while (current -> str[i])
	{
		if (current->str[0] == '|')
		{
			{
				printf("minishell: syntax error: mismatched pipes\n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	check_doubled_pipe(t_token *token)
{
	t_token	*current;

	current = token;
	if (!current)
		return (1);
	while (current)
	{
		if (current->token_type == PIPE)
		{
			if (!current->next)
			{
				printf("> nothing after pipe\n");
				return (1);
			}
			else if (current->next->token_type == PIPE)
			{
				printf("minishell: syntax error: mismatched pipes\n");
				return (1);
			}
		}
		current = current->next;
	}
	return (0);
}
