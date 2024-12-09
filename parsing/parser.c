/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:41:07 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/08 19:30:13 by ayhamdou         ###   ########.fr       */
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
int	check_file_in(char *file_name)
{
	struct stat	filestat;

	if (stat(file_name, &filestat) == -1) 
	{
		perror("Error accessing file");
		return (-1);
	}
	if (!(filestat.st_mode & S_IRUSR))
	{
		fprintf(stderr, "Error: permission denied '%s'.\n", file_name);
		return (-1);
	}
	return (0);
}
int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == -1)
	{
		perror("stat\n");
		return (-1);
	}
	if (S_ISDIR(path_stat.st_mode))
		return (-1); 
	return (0);
}
int check_file_out(char *file_name)
{
	struct stat filestat;

	stat(file_name, &filestat);
	if (!(filestat.st_mode & S_IWUSR)) 
	{
		fprintf(stderr, "Error: permission denied fnudgljrfkl'%s'.\n", file_name); // remove every fprintf
		return -1;
	}
	return(0);
}
char	*is_expand(char *str,int exp_flag, t_env *ev)
{
	char *res;
	// printf ("res = %p", res);
	// int	i = 0;
	// char tmp[2];
	char *expanded;

	if (!exp_flag)
	{
		expanded = NULL;
		res = ft_strdup("");
		expand_it(str, &res, &expanded, ev);
		// while (str[i])
		// {
		// 	if (str[i] == '$' && (ft_isalpha(str[i + 1]) || str[i + 1] == '_'))
		// 	{
		// 		i++;
		// 		expanded = ret_env(str, &i, ev);
		// 		res = ft_strjoin(res, expanded);
		// 		free(expanded);
		// 	}
		// 	else
		// 	{
		// 		tmp[0] = str[i];
		// 		tmp[1] = '\0';
		// 		res = ft_strjoin(res, tmp);
		// 		i++;
		// 	}
		// }
		free(str);
		return (res);
	}
	return (str);
}

void lherdoc(t_redir *r, int pipe, int exp_flag, t_env *ev)
{
	char *str;

	(void)ev;
	(void)exp_flag;
	str = NULL;
	while (1)
	{
		signal(SIGINT, handle_sig);
		signal(SIGQUIT, SIG_IGN);
		str = readline("herdoc> ");
		if (!str || ft_strcmp(str, r->filename) == 0)
		{
			free (str);
			str = NULL;
			close (pipe);
			break ;
		}
		str = /*ft_strdup(*/is_expand(str, exp_flag,ev)/*)*/;
		// dup2(STDOUT_FILENO,pipe);
		write (pipe, str, ft_strlen(str));
		write (pipe, "\n", 1);
		free(str);
	}
}
// int check_on_quotes(t_redir *red)
// {
// 	if (red->q_type == NONE)
// 		return (0);
// 	return (1);
// }

void	check_on_herdoc(t_redir *r, t_env *ev)
{
	int ld[2];
	int exp_flag;
	
	// exp_flag = check_on_quotes(r);
	if (r->q_type != NONE)
		exp_flag = 1;
	else
		exp_flag = 0;
	if ((pipe(ld)) == - 1)
		return;
	lherdoc(r, ld[1], exp_flag, ev);
	r->fd = ld[0];
	dup2(ld[0], STDIN_FILENO);
	close(ld[0]);
}

int	has_space(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

int	ambigious_check(t_redir *r, t_env *ev)
{
	t_redir *tmp;

	if (!r || !ev)
		return (0);
	tmp = r;
	if (!tmp -> filename || has_space(tmp->filename))
	{
		printf("ambiguous redirect\n");
		return (1);
	}
	return(0);
}

int open_files(t_command **commands, t_env *ev)
{
	if (!*commands)
		return (1);

	t_command *tmp;
	t_redir *r;
	tmp = *commands;
	while (*commands)
	{
		r = (*commands)->rederects;
		while (r)
		{
			if (ambigious_check(r, ev) == 1)
				return (1);
			if (r ->type == R_IN)
			{
				if (check_file_in(r->filename) == -1 || is_directory(r->filename) == -1)
					return (1);
				r->fd = open(r->filename, O_RDONLY);
			}
			else if (r -> type == R_OUT)
			{
				r->fd = open(r->filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
				if (check_file_out(r->filename) == -1 || is_directory(r->filename) == - 1)
				{
					close(r -> fd);
					return (1);
				}
			}
			else if (r->type == APP)
			{
				r->fd = open(r->filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
				if (check_file_out(r->filename) == -1 || is_directory(r->filename) == - 1)
				{
					close(r -> fd);
					return (1);
				}
			}
			else if (r -> type == HER)
				check_on_herdoc(r,ev);
			r = r -> next;
		}
		*commands = (*commands) -> next;
	}
	*commands = tmp;
	return (0);
}

void print_env(t_command *cmd, t_env *env)
{
    int i;
	int fd;
	fd = rederctes_out(cmd->rederects);
    while (env)
    {
        i = 0;
        while (cmd->args[i])
        {
            if (env->key && env->value)
            {
                if (check_equal(cmd->args[i]) == 1)
                {
                    // printf("%s=%s\n", env->key, env->value);
					write(fd, env->key, ft_strlen(env->key));
					write(fd, "=", 1);
					write(fd, env->value, ft_strlen(env->value));
					write(fd, "\n", 1);
                }
            }
            else if (env->key)
                {
                    if (check_equal(cmd->args[i]) == 0)
					{
						write(fd, env->key, ft_strlen(env->key));
						write(fd, "\n", 1);
					}
                }
            i++;
        }
        env = env->next;
    }
}

void exec_builtin(t_command *command,t_env *ev)
{
	if (!command)
		return ;
	(void)ev;
	if (!ft_strcmp(command->args[0], "echo"))
		the_echo(command);
	else if (!ft_strcmp(command -> args[0], "cd"))
		the_cd(command,ev);
	else if (!ft_strcmp(command -> args[0], "pwd"))
		the_pwd(command -> rederects, ev);
	else if (!ft_strcmp(command -> args[0], "export"))
		the_export(command,&ev);
	else if (!ft_strcmp(command -> args[0], "unset"))
		the_unset(command, &ev);
	else if (!ft_strcmp(command -> args[0], "env") && !command -> args[1])
		print_env(command ,ev);
	else if (!ft_strcmp(command->args[0], "exit"))
		ft_exit(command);
	// return (0);
}

char  *get_path(t_command *command,t_env *env)
{
	char *path;
	char **paths;
	int i;
	if (!command)
		return (NULL);
	path = ft_getenv(env, "PATH");
	paths = ft_split(path, ':');
	i = 0;
	while (paths[i])
	{
		if (paths[i][ft_strlen(paths[i]) - 1] != '/')
		{
		paths[i] = ft_strjoin(paths[i], "/");
		paths[i] = ft_strjoin(paths[i], command -> args[0]);	
		}
		if (access(paths[i], F_OK) == 0)
		{
			command -> args[0] = paths[i];
			return (paths[i]);
		}
		i++;
	}
	return (NULL);
}

void exec_single(t_command *command,t_env *ev, char **env)
{
	char *s;
	s = command -> args[0];

	if (command -> is_builtin)
		exec_builtin(command,ev);
	else
	{
		if (!s)
			return;
		if (command -> args[0][0] != '/')
			s = get_path(command, ev);
		pid_t pid = fork();
		if (pid == 0)
		{
			if (command -> rederects)
			{
				t_redir *r = command -> rederects;
				while (r)
				{
					if (r -> type == R_IN)
						dup2(r -> fd, 0);
					else if (r -> type == R_OUT || r -> type == APP)
						dup2(r -> fd, 1);
					r = r -> next;
				}
			}
			execve(s, command -> args, env);
			printf("%s: command not found\n",command -> args[0]);
			exit(1);
		}
		else
		{
			waitpid(pid, NULL, 0);
		}
	}
}
void	exec_command(t_command *command,t_env *ev,char **env)
{
	if (!command || !command->args)
		return ;
	if (!command -> next)
		exec_single(command ,ev,env);
	// else
	// {
	// 	int fd[2] = pipe();
	// 	dup2(fd[0], STDOUT_FILENO);
	// }
}

void exec(t_command *commands, t_env *ev, char **env)
{
	(void)ev;
	if (!commands)
		return ;
	if (open_files(&commands, ev) == 1)
		return ;
	exec_command(commands,ev,env);
	// printf("%s",commands -> args[0]);
}
int	parser(char *user_inp, t_env *ev,char **env)
{
	t_token		*token_list;
	t_command	*commands;
	(void)env;

	commands = NULL;
	token_list = NULL;
	tokenizer(user_inp, &token_list);
	if (lexer(token_list))
	{
		clean_tokens(&token_list);
		return (1);
	}
	expander(&token_list, ev);
	// printtokens(token_list);
	remove_quotes(&token_list);
	extract_cmds(token_list, &commands);
	check_last(commands);
	check_last_out(commands);
	// printcommnads(commands);
	exec(commands, ev, env);
	clean_tokens(&token_list);
	clean_cmds(&commands);
	return (0);
}


// TODO : create function helpers (create commnad ...) (do it later);
