/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:41:07 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/09/24 11:51:21 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	tokenizer(char *userInp)
{
	int		i;
	char	**splittedArg;

	i = 0;
	splittedArg = ft_split(userInp, ' ');
	while (splittedArg[i])
	{
		/* code */
	}
	
	
}

void	parser(char *userInp)
{
	t_token *tokenList = NULL;
	tokenizer(userInp);
}
