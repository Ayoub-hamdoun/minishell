/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_helper_0.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:44:06 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/16 20:32:13 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_token(t_token **token, char *data, t_etype type, t_etype qt)
{
	t_token	*tmp;
	t_token	*current;

	current = (t_token *)ft_malloc(sizeof(t_token));
	current->str = ft_strdup(data);
	current->token_type = type;
	current->q_type = qt;
	current->next = NULL;
	current->prev = NULL;
	if (!(*token))
		*token = current;
	else
	{
		tmp = *token;
		while (tmp->next)
			tmp = tmp->next;
		current->prev = tmp;
		tmp->next = current;
	}
}
