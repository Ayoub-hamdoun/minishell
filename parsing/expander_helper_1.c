/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helper_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 01:48:01 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/21 14:57:55 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ret_env(char *str, int *i, t_env *ev)
{
	int		start;
	char	*env;
	char	*res;

	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	env = ft_substr(str, start, (*i) - start);
	res = ft_getenv(ev, env);
	if (res)
		return (ft_strdup(res));
	return (ft_strdup(""));
}

char	*remove_chars(char *token)
{
	int		len;
	int		j;
	int		i;
	char	*new_content;

	if (!token)
		return (NULL);
	len = ft_strlen(token);
	new_content = ft_malloc(len + 1);
	i = 0;
	j = 0;
	while (token[i])
	{
		if (token[i] == '$' && is_quote(token[i + 1]))
			i++;
		else if (is_quote(token[i]))
			i++;
		else
			new_content[j++] = token[i++];
	}
	new_content[j] = '\0';
	return (new_content);
}

void	is_expandable(t_token **tokens, int *is_exp)
{
	*is_exp = 1;
	if ((*tokens)->prev)
	{
		if ((*tokens)->prev->token_type == HER)
			*is_exp = 0;
		else
			*is_exp = 1;
	}
}

int	has_tilda(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '~')
			return (1);
		i++;
	}
	return (0);
}
