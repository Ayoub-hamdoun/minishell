/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 08:46:04 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/03 16:52:32 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_red(t_token **token_list, char *trimmed, int *pos)
{
	if (trimmed[*pos] == '>')
	{
		if (trimmed[*pos + 1] == '>')
		{
			create_token(token_list, ">>", APP, NONE);
			(*pos)++;
		}
		else
			create_token(token_list, ">", R_OUT, NONE);
	}
	else if (trimmed[*pos] == '<')
	{
		if (trimmed[*pos + 1] == '<')
		{
			create_token(token_list, "<<", HER, NONE);
			(*pos)++;
		}
		else
			create_token(token_list, "<", R_IN, NONE);
	}
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
	check_red(token_list, trimmed, &pos);
	pos++;
	if (str)
		free(str);
	return (pos);
}

void	check_quots_type(char *quote, char q, t_etype *qtype)
{
	*quote = q;
	if (*quote == '\"')
		*qtype = DOUBLE;
	else if (*quote == '\'')
		*qtype = SINGLE;
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
		if ((trimmed[pos] == '\'' || trimmed[pos] == '\"') && !quote)
			check_quots_type(&quote, trimmed[pos], &qt);
		else if (trimmed[pos] == quote)
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

void	tokenizer(char *user_inp, t_token **token_list)
{
	int		i;
	char	*trimmed;

	i = 0;
	trimmed = ft_strtrim(user_inp, " \t");
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
