/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper_0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:13:07 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/16 20:35:57 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_word(t_command **command, char *str, int *argcount)
{
	int		i;
	char	**updated_args;

	if (!(*command)->args)
	{
		(*command)->args[0] = ft_strdup(str);
		(*command)->args[1] = NULL;
		*argcount = 1;
	}
	else
	{
		updated_args = (char **)ft_malloc(((*argcount) + 2) * sizeof(char *));
		i = 0;
		while (i < (*argcount))
		{
			updated_args[i] = (*command)->args[i];
			i++;
		}
		updated_args[(*argcount)] = ft_strdup(str);
		updated_args[(*argcount) + 1] = NULL;
		////free((*command)->args);
		(*command)->args = updated_args;
		(*argcount)++;
		(*command)->is_builtin = is_builtin((*command)->args[0]);
	}
}

void	handle_redirections(t_command *command, t_token **token_list)
{
	t_redir	*redir;
	t_redir	*tmp;

	if (!(*token_list)->next)
		return ;
	redir = (t_redir *) ft_malloc(sizeof(t_redir));
	if (!redir)
		return ;
	redir->type = (*token_list)->token_type;
	*token_list = (*token_list)->next;
	redir->filename = ft_strdup((*token_list)->str);
	redir->flag_in = 0;
	redir->flag_out = 0;
	redir->q_type = (*token_list)->q_type;
	redir->next = NULL;
	if (!(command->rederects))
		command->rederects = redir;
	else
	{
		tmp = command->rederects;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = redir;
	}
}

int is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}
