/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:41:07 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/02 18:23:38 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_command	*cmd_new(t_command **commands)
{
	t_command	*cmd;

	cmd = (t_command *)malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = (char **)malloc(2 * sizeof(char *));
	cmd->args[0] = NULL;
	cmd->args[1] = NULL;
	cmd->is_builtin = 0;
	cmd->rederects = NULL;
	cmd->next = NULL;
	if (!(*commands))
		*commands = cmd;
	return (cmd);
}

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
		updated_args = (char **)malloc(((*argcount) + 2) * sizeof(char *));
		i = 0;
		while (i < (*argcount))
		{
			updated_args[i] = (*command)->args[i];
			i++;
		}
		updated_args[(*argcount)] = ft_strdup(str);
		updated_args[(*argcount) + 1] = NULL;
		free((*command)->args);
		(*command)->args = updated_args;
		(*argcount)++;
	}
}

void	handle_redirections(t_command *command, t_token **token_list)
{
	t_redir	*redir;
	t_redir	*tmp;

	if (!(*token_list)->next)
		return ;
	redir = (t_redir *) malloc(sizeof(t_redir));
	if (!redir)
		return ;
	redir->type = (*token_list)->token_type;
	*token_list = (*token_list)->next;
	redir->filename = ft_strdup((*token_list)->str);
	redir->flag_in = 0;
	redir->flag_out = 0;
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

t_command	*handle_pip(t_command *command, t_command **commands)
{
	if (!command)
		command = cmd_new(commands);
	else
	{
		command->next = cmd_new(commands);
		command = command->next;
	}
	return (command);
}

void	check_command(t_command **command, t_command ***commands)
{
	if (!(*command))
		(*command) = cmd_new(&(**commands));
}


void	extract_cmds(t_token *tokens, t_command **commands)
{
	t_command	*command;
	int			argcount;

	command = NULL;
	argcount = 0;
	while (tokens)
	{
		if (tokens->token_type == WORD || tokens->token_type == ENV)
		{
			check_command(&command, &commands);
			handle_word(&command, tokens->str, &argcount);
		}
		else if (tokens->token_type == R_OUT || tokens->token_type == R_IN
			|| tokens->token_type == HER || tokens->token_type == APP)
		{
			check_command(&command, &commands);
			handle_redirections(command, &tokens);
		}
		else if (tokens->token_type == PIPE)
		{
			command = handle_pip(command, commands);
			argcount = 0;
		}
		tokens = tokens->next;
	}
}

int	parser(char *userInp)
{
	t_token 	*token_list;
	t_command 	*commands;

	commands = NULL;
	token_list = NULL;
	tokenizer(userInp, &token_list);
	// lexer(token_list);
	expander(&token_list);
	// printtokens(token_list);
	remove_quotes(&token_list);
	extract_cmds(token_list, &commands);
	check_last(commands);
	check_last_out(commands);
	printcommnads(commands);
	return (0);
}


// TODO : create function helpers (create commnad ...) (do it later);
