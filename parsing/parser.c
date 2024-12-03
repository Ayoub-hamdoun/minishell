/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:41:07 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/03 21:17:50 by ayhamdou         ###   ########.fr       */
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
int check_file_in(char *file_name)
{
	//ambigious check

	struct stat filestat;

	if (stat(file_name, &filestat) == -1) 
	{
		perror("Error accessing file");
		return -1;
	}
	if (!(filestat.st_mode & S_IRUSR)) 
	{
		fprintf(stderr, "Error: permission denied '%s'.\n", file_name);
		return -1;
	}
	return 0;
}
int is_directory(const char *path)
{
    struct stat path_stat;
    if (stat(path, &path_stat) == -1)
    {
        perror("stat");
        return -1;
    }

    if (S_ISDIR(path_stat.st_mode))
        return -1; 
	return (0);
}
int check_file_out(char *file_name)
{
	struct stat filestat;
		stat(file_name, &filestat);
		
		if (!(filestat.st_mode & S_IWUSR)) 
	{
		fprintf(stderr, "Error: permission denied'%s'.\n", file_name);
		return -1;
	}
	return(0);
}
void lherdoc(t_redir *r,int pipe)
{
	char *str;

	str = NULL;
	while (1)
	{
		str = readline("herdo>");
		if (!str || ft_strcmp(str, r->filename) == 0)
		{
			free (str);
			str = NULL;
			close (pipe);
			break ;
		}
		write (pipe, str, ft_strlen(str));
		write (pipe, "\n", 1);
	}
}
void check_on_herdoc(t_redir *r)
{
	int ld[2];

	if ((pipe(ld)) == - 1)
		return;
	lherdoc(r,ld[1]);
	r->fd = ld[0];
}
void open_files(t_command **commands)
{
	if (!*commands)
		return ;
		
	t_command *tmp;
	t_redir *r;
	tmp = *commands;
	while (*commands)
	{
		r = (*commands)->rederects;
		while (r)
		{
			if (r ->type == R_IN)
			{
				if (check_file_in(r->filename) == -1 || is_directory(r->filename) == -1)
					return ;
				r->fd = open(r->filename, O_RDONLY);
			}
			else if (r -> type == R_OUT)
			{
				r->fd = open(r->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (check_file_out(r->filename) == -1 || is_directory(r->filename) == - 1)
				{
					close(r -> fd);
					return ;
				}
			}
			else if (r->type == APP)
			{
				r->fd = open(r->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (check_file_out(r->filename) == -1 || is_directory(r->filename) == - 1)
				{
					close(r -> fd);
					return ;
				}
			}
			else if (r -> type == HER)
				check_on_herdoc(r);
			r = r -> next;
		}
		*commands = (*commands) -> next;
	}
}
void exec(t_command *commands)
{
	if (!commands)
		return ;
	open_files(&commands);
}
int	parser(char *user_inp, t_env *ev)
{
	t_token		*token_list;
	t_command	*commands;

	commands = NULL;
	token_list = NULL;
	tokenizer(user_inp, &token_list);
	if (lexer(token_list))
		return (1);
	expander(&token_list, ev);
	// printtokens(token_list);
	remove_quotes(&token_list);
	extract_cmds(token_list, &commands);
	check_last(commands);
	check_last_out(commands);
	// printcommnads(commands);
	exec(commands);
	return (0);
}


// TODO : create function helpers (create commnad ...) (do it later);
