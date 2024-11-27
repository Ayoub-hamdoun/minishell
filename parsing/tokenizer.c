/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallali <rallali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 08:46:04 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/11/27 03:47:21 by rallali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_token(t_token **token, char *data, t_etype type, t_etype qt)
{
	t_token	*tmp;
	t_token	*current;

	current = (t_token *)malloc(sizeof(t_token));
	current->str = ft_strdup(data);
	// if (qt != NONE)
	// 	rm_qt(current->str);
	current->tokenType = type;
	current->q_type = qt;
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
	int h;
	char *str;

	str = NULL;
	if (trimmed[pos] == '|')
		create_token(token_list, "|", PIPE, NONE);
	else if (trimmed[pos] == '$')
	{
		h = pos;
		while (trimmed[pos] && (trimmed[pos] != ' ' && trimmed[pos] != '\t'))
			pos++;
		str = ft_substr(trimmed, h, pos - h);
		create_token(token_list, str, ENV, NONE);
	}
	//check for ~
	else if (trimmed[pos] == '>')
	{
		if (trimmed[pos + 1] == '>')
		{
			create_token(token_list, ">>", APP, NONE);
			pos++;
		}
		else
			create_token(token_list, ">", R_OUT, NONE);
	}
	else if (trimmed[pos] == '<')
	{
		if (trimmed[pos + 1] == '<')
		{
			create_token(token_list, "<<", HER, NONE);
			pos++;
		}
		else
			create_token(token_list, "<", R_IN, NONE);
	}
	pos++;
	if (str)
		free(str);
	return (pos);
}

int is_normal_word(char *trimmed, int pos, t_token **token_list)
{
	int		start;
	char	quote;
	char	*str;
	t_etype	qt;

	start = pos;
	qt = NONE;
	if (trimmed[pos] == '\'' || trimmed[pos] == '\"')
	{
		quote = trimmed[pos];
		pos++;
		while (trimmed[pos] && trimmed[pos] != quote)
			pos++;
		pos++;
		if (quote == '\"')
			qt = DOUBLE;
		else
			qt = SINGLE;
	}
	else
	{
		while (trimmed[pos] && trimmed[pos] != ' ' && trimmed[pos] != '|' && trimmed[pos] != '>' && trimmed[pos] != '<' )
			pos++;
	}
	str = ft_substr(trimmed, start, pos - start);
	create_token(token_list, str, WORD, qt);
	if (str)
		free(str);
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
		while (trimmed[i] == ' ' || trimmed[i] == '\t') // add white spaces
			i++;
		if (!trimmed[i])
			break ;
		if (trimmed[i] == '|' || trimmed[i] == '>' || trimmed[i] == '<'
			|| trimmed[i] == '$')
			i = is_special_char(trimmed, token_list, i);
		else
			i = is_normal_word(trimmed, i, token_list);
	}
	free(trimmed);
}
//TODO: handl leaks ;;;;
//TODO: don t pass only spaces " "
//TODO: handle if there is one quote it should not be contained in the word more like a syntax error example '$ or $' or $" or "$
//TODO: