/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallali <rallali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 08:46:04 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/02 19:23:51 by rallali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_token(t_token **token, char *data, t_etype type, t_etype qt)
{
	t_token	*tmp;
	t_token	*current;

	current = (t_token *)malloc(sizeof(t_token));
	current->str = ft_strdup(data);
	current->token_type = type;
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

int	check_in_or_herdoc(char *trimmed, t_token **token_list, int pos)
{
	if (trimmed[pos] == '<')
	{
		if (trimmed[pos + 1] == '<')
		{
			create_token(token_list, "<<", HER, NONE);
			pos++;
		}
		else
			create_token(token_list, "<", R_IN, NONE);
	}
	return (pos);
}

int	check_out_or_append(char *trimmed, t_token **token_list, int pos)
{
	if (trimmed[pos] == '>')
	{
		if (trimmed[pos + 1] == '>')
		{
			create_token(token_list, ">>", APP, NONE);
			pos++;
		}
		else
			create_token(token_list, ">", R_OUT, NONE);
	}
	return (pos);
}

int	is_special_char(char *trimmed, t_token **token_list, int pos)
{
	int		h;
	char	*str;

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
		free (str);
		return (pos);
	}
	pos = check_out_or_append(trimmed, token_list, pos);
	pos = check_in_or_herdoc(trimmed, token_list, pos);
	pos++;
	if (str)
		free(str);
	return (pos);
}

void	check_one_quote(char *trimmed, char *quote, int pos, t_etype *qt)
{
	if ((trimmed[pos] == '\'' || trimmed[pos] == '\"') && !(*quote))
	{
		*quote = trimmed[pos];
		if (*quote == '\"')
			*qt = DOUBLE;
		else if (*quote == '\'')
			*qt = SINGLE;
	}
}

int	is_normal_word(char *trimmed, t_token **token_list, int pos)
{
	int		start;
	char	quote;
	char	*str;
	t_etype	qt;

	start = pos;
	quote = '\0';
	qt = NONE;
	while (trimmed[pos])
	{
		check_one_quote(trimmed, &quote, pos, &qt);
		if (trimmed[pos] == quote)
			quote = '\0';
		else if (quote == '\0' && (trimmed[pos] == ' ' || trimmed[pos] == '|'
				|| trimmed[pos] == '>' || trimmed[pos] == '<'))
			break ;
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
		while (trimmed[i] == ' ' || trimmed[i] == '\t')
			i++;
		if (!trimmed[i])
			break ;
		if (trimmed[i] == '|' || trimmed[i] == '>' || trimmed[i] == '<'
			|| trimmed[i] == '$')
			i = is_special_char(trimmed, token_list, i);
		else
			i = is_normal_word(trimmed, token_list, i);
	}
	free(trimmed);
}
//TODO: handl leaks ;;;;
//TODO: don t pass only spaces " "
//TODO: handle if there is one quote it should not be contained in the word more like a syntax error example '$ or $' or $" or "$
//TODO: