/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 08:46:04 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/11/26 16:48:08 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_token(t_token **token, char *data, t_etype type)
{
	t_token	*tmp;
	t_token	*current;

	current = (t_token *)malloc(sizeof(t_token));
	current->str = data;
	current->tokenType = type;
	current->next = NULL;
	if (!(*token))
		*token = current;
	else
	{
		tmp = *token;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = current;
	}
}

int	is_special_char(char *trimmed, t_token **token_list, int pos)
{
	if (trimmed[pos] == '|')
		create_token(token_list, "|", PIPE);
	else if (trimmed[pos] == '>')
	{
		if (trimmed[pos + 1] == '>')
		{
			create_token(token_list, ">>", APP);
			pos++;
		}
		else
			create_token(token_list, ">", R_OUT);
	}
	else if (trimmed[pos] == '<')
	{
		if (trimmed[pos + 1] == '<')
		{
			create_token(token_list, "<<", HER);
			pos++;
		}
		else
			create_token(token_list, "<", R_IN);
	}
	pos++;
	return (pos);
}

int is_normal_word(char *trimmed, int pos, t_token **token_list)
{
	int	start;

	start = pos;
	if (trimmed[pos] == '\'' || trimmed[pos] == '\"')
	{
		pos++;
		while (trimmed[pos] && trimmed[pos] != '\'' && trimmed[pos] != '\"')
			pos++;
	}
	else
	{
		while (trimmed[pos] && trimmed[pos] != ' ' && trimmed[pos] != '|')
			pos++;
	}
	pos++;
	create_token(token_list, ft_substr(trimmed, start, pos - start), WORD);
	return (pos);
}

void	tokenizer(char *userInp, t_token **token_list)
{
	int		i;
	char	*trimmed;

	i = 0;
	trimmed = ft_strtrim(userInp, " \t");
	while (trimmed[i])
	{
		if (trimmed[i] == ' ' || trimmed[i] == '\t')
			i++;
		if (trimmed[i] == '|' || trimmed[i] == '>' || trimmed[i] == '<')
			i = is_special_char(trimmed, token_list, i);
		else
			i = is_normal_word(trimmed, i, token_list);
	}
}
//TODO: handl leaks ;;;;
//TODO: don t pass only spaces " "
//TODO: handle if there is one quote it should not be contained in the word more like a syntax error example '$ or $' or $" or "$
//TODO: