/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:41:07 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/11/26 17:04:17 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//SECTION - TMPFUNCTIONS

void printtokens(t_token *lst)
{
	int i = 0;

	while (lst)
	{
		i++;
		printf("\nTOKEN : -------------------------\n");
		printf("%d; content [%s] ; type [%d] ; qoute type [%d]", i, lst->str, lst->tokenType, lst->q_type);
		printf("\n---------------------------------\n");
		lst = lst->next;
	}
}
void printredirections(t_redir *lst)
{
	if (!lst)
		printf("\nno redirections");
	while (lst)
	{
		printf("\nREDIRECTIONS : ~~~~~~~~~~~~~~~~\n");
		printf("filename :[%s], file type [%d]", lst->filename, lst->type);
		printf("\n~~~~~~~~~~~~~~~~\n");
		lst = lst->next;
	}
}

void printcommnads(t_command *lst)
{
	int i = 0;

	if (!lst)
		printf("no commands");
	while (lst)
	{
		printf("\nCOMMANDS : ---------------------------------\n");
		while (lst->args[i])
		{
			printf("'%s' ", lst->args[i]);
			i++;
		}
		i = 0;
		printf ("\n%d", lst->is_builtin);
		printredirections(lst->rederects);
		printf("\n---------------------------------\n");
		lst = lst->next;
	}
}


void exit_funcs()
{
	printf("\nSYNTAX ERROR\n");
}
//!SECTION END TMPFUNCTIONS

void	validat_syntax(t_token *tokens)
{
	//temp solution :
	int i;

	i = 0;
	while (tokens)
	{
		if (tokens->tokenType == R_IN || tokens->tokenType == R_OUT)
		{
			if (!tokens->next || tokens->next->tokenType != WORD)
				exit_funcs();
		}
		else if (tokens->tokenType == PIPE)
		{
			if (tokens->next->tokenType == PIPE)
				exit_funcs();
		}
		tokens = tokens->next;
	}
}

void extract_cmds(t_token *token_list, t_command **commands)
{
	t_command *command;
	t_redir *redir;
	t_redir *tmp;
	char **updated_args;
	int argcount = 0;
	int i = 0;

	command = NULL;
	updated_args = NULL;
	while (token_list)
	{
		// new commnad
		if (token_list->tokenType == WORD)
		{
			if (!command)
			{
				command = (t_command *)malloc(sizeof(t_command));
				command->args = (char **)malloc(2 * sizeof(char *));
				command->args[0] = strdup(token_list->str);
				command->args[1] = NULL;
				argcount = 1;
				command->is_builtin = 0;
				command->rederects = NULL;
				command->next = NULL;
				if (!(* commands))
					*commands = command;
			}
			else
			{
				// Add the new argument
				updated_args = (char **)malloc((argcount + 2) * sizeof(char *));
				i = 0;
				while (i < argcount)
				{
					updated_args[i] = command->args[i];
					i++;
				}
				updated_args[argcount] = ft_strdup(token_list->str);
				updated_args[argcount + 1] = NULL;
				free(command->args);
				command->args = updated_args;
				argcount++;
			}
		}
		else if (token_list->tokenType == R_OUT || token_list->tokenType == R_IN || token_list->tokenType == HER)
		{
			if (!token_list->next)
				break ;
			token_list = token_list->next;
			redir = (t_redir *) malloc(sizeof(t_redir));
			redir->filename = ft_strdup(token_list->str);
			redir->type = token_list->tokenType;
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
		else if (token_list->tokenType == PIPE)
		{
			command->next = (t_command *)malloc(sizeof(t_command));
			command->next->args = (char **)malloc(2 * sizeof(char *));
			command->next->args[0] = NULL;
			command->next->is_builtin = 0;
			command->next->next = NULL;
			command = command->next;
			argcount = 0;
		}
		token_list = token_list->next;
	}
}

int	parser(char *userInp)
{
	t_token *token_list;
	t_command *commands;

	commands = NULL;
	token_list = NULL;
	tokenizer(userInp, &token_list);
	// lexer(token_list);
	expander(&token_list);
	printtokens(token_list);
	// validat_syntax(token_list);
	// extract_cmds(token_list, &commands);
	// printcommnads(commands);
	// clean_tokens(&token_list);
	return (0);
}
