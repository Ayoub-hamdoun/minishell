/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:41:07 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/09/24 14:57:12 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void printtokens(t_token *lst)
{
	while (lst)
	{
		printf("\n---------------------------------\n");
		printf("%s : %d", lst->str, lst->tokenType);
		printf("\n---------------------------------\n");
		lst = lst->next;
	}
}

void	tokenizer(char *userInp, t_token **tokenList)
{
	int		i;
	char	**splitted_arg;
	t_token *token;
	t_token *tmp;

	i = 0;
	splitted_arg = ft_split(userInp, ' ');
	while (splitted_arg[i])
	{
		token = (t_token *) malloc(sizeof(t_token));
		token->str = splitted_arg[i];
		if (!ft_strcmp(splitted_arg[i], ">"))
			token->tokenType = R_OUT;
		else if (!ft_strcmp(splitted_arg[i], "<"))
			token->tokenType = R_IN;
		else if ((!ft_strcmp(splitted_arg[i], "|")))
			token->tokenType = PIPE;
		else
			token->tokenType = WORD;
		token->next = NULL;
		i++;
		if (!(*tokenList))
			*tokenList = token;
		else
		{
			tmp = *tokenList;
			while (tmp && tmp->next)
				tmp = tmp->next;
			tmp->next = token;
		}
	}
}

void	parser(char *userInp)
{
	t_token *tokenList = NULL;

	tokenizer(userInp, &tokenList);
	printtokens(tokenList);
}
