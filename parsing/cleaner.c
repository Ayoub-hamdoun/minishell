/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:05:53 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/05 16:37:44 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	sizeofarray(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	free_2d(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (i < sizeofarray(array))
		{
			if (array[i])
				free(array[i]);
			i++;
		}
		free(array);
	}
}

void	clean_tokens(t_token **tokens)
{
	t_token	*tmp;

	while (*tokens)
	{
		tmp = *tokens;
		*tokens = (*tokens)->next;
		free(tmp->str);
		free(tmp);
	}
}

void	clean_red(t_redir **reds)
{
	t_redir	*tmp;

	while (*reds)
	{
		tmp = (*reds);
		*reds = (*reds)->next;
		free(tmp->filename);
		free(tmp);
	}
}

void	clean_cmds(t_command **cmds)
{
	t_command	*tmp = NULL;
	int			i;

	while (*cmds)
	{
		i = 0;
		tmp = *cmds;
		*cmds = (*cmds)->next;
		clean_red(&tmp->rederects);
		while (tmp->args[i])
			i++;
		while (i >= 0)
		{
			if (tmp->args[i])
				free(tmp->args[i]);
			i--;
		}
		free(tmp->args);
		free(tmp);
	}
}
