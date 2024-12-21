/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:35:54 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/21 20:02:06 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_error(char *err, int ret)
{
	ft_putstr_fd(err, 2);
	return (ret);
}

int	update_es(int ec, int ret)
{
	exit_status(ec);
	return (ret);
}

int	check_quotes(t_token *token)
{
	t_token	*current;
	int		i;
	char	quote;

	current = token;
	if (!current)
		return (1);
	while (current)
	{
		i = 0;
		quote = 0;
		while (current->str[i])
		{
			if ((current->str[i] == '\'' || current->str[i] == '\"') && !quote)
				quote = current->str[i];
			else if (current->str[i] == quote)
				quote = 0;
			i++;
		}
		if (quote)
			return (print_error("minishell: syntax error:\
				mismatched quotes\n", 1));
		current = current->next;
	}
	return (0);
}

int	lexer(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	if (check_first_p(tmp))
		return (update_es(258, 1));
	while (tmp)
	{
		if (check_redirection(tmp))
		{
			exit_status(258);
			return (1);
		}
		if (check_quotes(tmp))
		{
			exit_status(258);
			return (1);
		}
		if (check_doubled_pipe(tmp))
		{
			exit_status(258);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
