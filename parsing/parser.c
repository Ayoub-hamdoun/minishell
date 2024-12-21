/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:41:07 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/21 19:52:33 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_command	*cmd_new(t_command **commands)
{
	t_command	*cmd;

	cmd = (t_command *)ft_malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = (char **)ft_malloc(2 * sizeof(char *));
	cmd->args[0] = NULL;
	cmd->args[1] = NULL;
	cmd->is_builtin = 0;
	cmd->rederects = NULL;
	cmd->next = NULL;
	if (!(*commands))
		*commands = cmd;
	return (cmd);
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
			handle_word(&command, tokens->str, &argcount, tokens->has_expaned);
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

int	parser(char *user_inp, t_env *ev)
{
	t_token		*token_list;
	t_command	*commands;
	int			lex_flag;

	commands = NULL;
	token_list = NULL;
	lex_flag = 0;
	tokenizer(user_inp, &token_list);
	lex_flag = lexer(token_list);
	if (lex_flag)
		return (1);
	expander(&token_list, ev);
	// printtokens(token_list);
	remove_quotes(&token_list);
	extract_cmds(token_list, &commands);
	check_last(commands);
	check_last_out(commands);
	// printcommnads(commands);
	if (lex_flag == 0)
		exec(commands, ev);
	return (0);
}
