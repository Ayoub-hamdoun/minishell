/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:41:07 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/01 16:22:23 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//SECTION - TMPFUNCTIONS

char*	gettype(t_etype type)
{
	if (type == DOUBLE)
		return ("DOUBLE");
	else if (type == SINGLE)
		return "SINGLE";
	else if (type == NONE)
		return "NONE";
	else if (type == WORD)
		return "WORD";
	else if (type == R_IN)
		return "R_IN";
	else if (type == R_OUT)
		return "R_OUT";
	else if (type == APP)
		return "APP";
	else if (type == HER)
		return "HER";
	else if (type == ENV)
		return "ENV";
	else 
		return "PIPE";
}

void printtokens(t_token *lst)
{
	int i = 0;

	while (lst)
	{
		i++;
		printf("\nTOKEN : -------------------------\n");
		printf("%d; content [%s] ; type [%s] ; qoute type [%s]", i, lst->str, gettype(lst->tokenType), gettype(lst->q_type));
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
		printf("filename :[%s], file type [%s], in [%d], out [%d]", lst->filename, gettype(lst->type), lst->flag_in, lst->flag_out);
		printf("\n~~~~~~~~~~~~~~~~\n");
		lst = lst->next;
	}
}

void printcommnads(t_command *lst)
{
	int i = 0;

	// if (!lst)
	// 	printf("no commands\n");
	while (lst)
	{
		printf("\nCOMMANDS : ---------------------------------\n");
		while (lst->args[i])
		{
			printf("[%s] \n", lst->args[i]);
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
// need more explanation to do this
// void	last_file(t_command *commands)
// {

// }

void	remove_quotes(t_token **tokens)
{
	t_token	*current;
	char	*new_str;
	char	*tmp;
	char quote;
	int		i;
	int		start;

	current = *tokens;
	while (current)
	{
		if (current->q_type != NONE)
		{
			new_str = ft_strdup("");
			i = 0;
			while (current->str[i])
			{
				if (current->str[i] == '\'' || current->str[i] == '\"')
				{
					quote = current->str[i];
					i++;
					start = i;
					while (current->str[i] && current->str[i] != quote)
						i++;
					tmp = ft_substr(current->str, start, i - start); // Extract content inside quotes
					new_str = ft_strjoin(new_str, tmp);
					free(tmp);
					if (current->str[i] == quote)
						i++;
				}
				else
				{
					start = i;
					while (current->str[i] && current->str[i] != '\'' && current->str[i] != '\"')
						i++;
					tmp = ft_substr(current->str, start, i - start);
					new_str = ft_strjoin(new_str, tmp);
					free(tmp);
				}
			}
			free(current->str);
			current->str = new_str;
		}
		current = current->next;
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
	remove_quotes(&token_list);
	while (token_list)
	{
		// new commnad
		if (token_list->tokenType == WORD || token_list->tokenType == ENV)
		{
			if (!command)
			{
				command = (t_command *)malloc(sizeof(t_command));
				command->args = (char **)malloc(2 * sizeof(char *));
				command->args[0] = ft_strdup(token_list->str);
				command->args[1] = NULL;
				argcount = 1; //temp
				command->is_builtin = 0;
				command->rederects = NULL;
				command->next = NULL;
				// rm_middle_quotes(command->args[0]);
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
		// create red list if true
		else if (token_list->tokenType == R_OUT || token_list->tokenType == R_IN
			|| token_list->tokenType == HER || token_list->tokenType == APP)
		{
			if (!token_list->next)
				break ;
			if (!command) // if !commnd create a new command with empty args
			{
				command = (t_command *)malloc(sizeof(t_command));
				command->args = (char **)malloc(2 * sizeof(char *));
				command->args[0] = NULL;
				command->args[1] = NULL;
				argcount = 0; //temp
				command->is_builtin = 0;
				command->rederects = NULL;
				command->next = NULL;
				if (!(* commands))
					*commands = command;
			}
			redir = (t_redir *) malloc(sizeof(t_redir));
			redir->type = token_list->tokenType;
			token_list = token_list->next;
			redir->filename = ft_strdup(token_list->str);
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
		else if (token_list->tokenType == PIPE)
		{
			command->next = (t_command *)malloc(sizeof(t_command));
			command->next->args = (char **)malloc(2 * sizeof(char *));
			command->next->args[0] = NULL;
			command->next->is_builtin = 0;
			command->next->rederects = NULL;
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
	lexer(token_list);
	expander(&token_list);
	printtokens(token_list);
	// validat_syntax(token_list);
	extract_cmds(token_list, &commands);
	check_last(commands);
	check_last_out(commands);
	printcommnads(commands);
	// last_file(&commands);
	// clean_tokens(&token_list);
	return (0);
}


// TODO : create function helpers (create commnad ...) (do it later);
