/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:41:07 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/09/25 15:09:12 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//NOTE - TMPFUNCTIONS
void printtokens(t_token *lst)
{
	while (lst)
	{
		printf("\nTOKENS : ---------------------------------\n");
		printf("%s : %d", lst->str, lst->tokenType);
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
		printf("filename :%s, file type %d", lst->filename, lst->type);
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
//NOTE - END TMPFUNCTIONS

void	tokenizer(char *userInp, t_token **tokenList)
{
	int		i;
	char	**splitted_arg;
	t_token *token;
	t_token *tmp;

	i = 0;
	splitted_arg = ft_split(userInp, ' ');
	while (splitted_arg[i])
	{
		token = (t_token *) malloc(sizeof(t_token));
		token->str = splitted_arg[i];
		if (!ft_strcmp(splitted_arg[i], ">"))
			token->tokenType = R_OUT;
		else if (!ft_strcmp(splitted_arg[i], "<"))
			token->tokenType = R_IN;
		else if ((!ft_strcmp(splitted_arg[i], "|")))
			token->tokenType = PIPE;
		else
			token->tokenType = WORD;
		token->next = NULL;
		i++;
		if (!(*tokenList))
			*tokenList = token;
		else
		{
			tmp = *tokenList;
			while (tmp && tmp->next)
				tmp = tmp->next;
			tmp->next = token;
		}
	}
}

void extract_cmds(t_token *token_list, t_command **commands)
{
	t_command *command;
	// t_command *tmp;
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
		else if (token_list->tokenType == R_OUT || token_list->tokenType == R_IN || token_list->tokenType == HER )
		{
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
			// token_list = token_list->next;
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
	extract_cmds(token_list, &commands);
	// commands = parse_tokens(token_list);
	// printtokens(token_list);
	printcommnads(commands);
	
	return (0);
}
