/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallali <rallali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:40:38 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/19 20:29:58 by rallali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
// libs
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <limits.h>
#include <stddef.h>

extern int g_exit_status;

typedef enum type
{
	DOUBLE,	//double quote ...
	SINGLE,
	NONE, // no quote
	WORD,
	R_IN,
	R_OUT,
	APP,
	HER,
	ENV,
	PIPE
}	t_etype;

// Token structure
typedef struct s_token
{
	char			*str;
	t_etype			token_type;
	t_etype			q_type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

// Redirection structure
typedef struct s_redir
{
	char			*filename;
	int				flag_in;
	int				flag_out;
	int				fd;
	int				is_open;
	int				check_her;
	t_etype			type;
	t_etype			q_type;
	struct s_redir	*next;
}	t_redir;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

// Command structure
typedef struct s_command
{
	char				**args;
	int					is_builtin;
	struct s_redir		*rederects;
	struct s_command	*next;
}	t_command;

typedef struct s_vars
{
	int		i;
	int		argcount;
	char	**args;
}	t_vars;

typedef struct s_grbdg {
    void *ptr;
    struct s_grbdg *next;
} t_grbdg;

// parsing funcs
int		parser(char *user_inp, t_env *ev);
void	handle_word(t_command **command, char *str, int *argcount);
void	handle_redirections(t_command *command, t_token **token_list);
void	tokenizer(char *user_inp, t_token **tokenList);
void	create_token(t_token **token, char *data, t_etype type, t_etype qt);
void	expander(t_token **tokens, t_env *ev);
void	expand_it(char *str, char **res, char **expanded, t_env *ev);
char	*ret_env(char *str, int *i, t_env *ev);
int		has_quotes(char	*str);
void	update_token(t_token **token, char **res, t_env *ev);
int		lexer(t_token *tokens);
int		check_doubled_pipe(t_token *token);
int		check_first_p(t_token *token);
void	check_last_out(t_command *token);
void	check_last(t_command *token);
void	dup_env(t_env *env, char **ev);
char	*ft_getenv(t_env *env, char *key);
void	remove_quotes(t_token **tokens);
void	handle_sig(int sig);
int		is_builtin(char *cmd);
void	wait_for_all_processes(pid_t	last_pid);
// end of parsing func

// exec funcs
int		open_files(t_command **commands, t_env *ev);
int		has_space(char *str);
int		is_directory(const char *path);
int		file_checkers(char	*file_name, t_etype file_type);
int		check_file_in(char *file_name);
int		check_file_out(char *file_name);
char	*is_expand(char *str, int exp_flag, t_env *ev);
void	check_on_herdoc(t_redir *r, t_env *ev);
void	lherdoc(t_redir *r, int pipe, int exp_flag, t_env *ev);
void	exec(t_command *commands, t_env *ev);
int		exec_builtin(t_command *command,t_env *ev);
void	pipe_in(int prev_fd);
void	pipe_out(int pipe_fd[2]);
void	close_red(t_redir *r);
void	red_dup(t_redir **r);
int		exit_status(int status);

// end exec funcs

// cleaners
// void	clean_tokens(t_token **tokens);
// void	clean_cmds(t_command **cmds);
// void	clean_red(t_redir **reds);
int		sizeofarray(char **array);
void 	free_all(void);
void *ft_malloc(size_t size);
int	sizeofarray(char **array);
void add(void *ptr);

// utils
int		ft_strlen(char	*str);
char	**ft_split(char *s, char c);
char	*ft_strtrim(char *s1, char *set);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(char *s1);
char	*ft_substr(char *s, int start, int len);
char	*ft_strjoin(char *s1, char *s2);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
char	*ft_strchr(char *str, int c);
void	ft_putstr_fd(char *s, int fd);
void	put_err(char *str, int is_exit);

//temp
void 	printtokens(t_token *lst);
void	printredirections(t_redir *lst);
void	printcommnads(t_command *lst);
char	*gettype(t_etype type);
void	exit_funcs(void);
void	print_envp(char **envp);
void	print_e(t_env *ev);
int	print_env(t_command *cmd, t_env *env);
//end temp

//builtins
int		rederctes_out(t_redir *reder);
int		check_equal(char *cmd);
int		the_export(t_command *cmd, t_env **env);
int		the_echo(t_command *cmd);
void		ft_exit(t_command *command);
int		the_cd(t_command *cmd, t_env *env);
int		the_pwd(t_redir *reder, t_env *env);
int		the_unset(t_command *cmd, t_env **env);
void	update_oldpwd(char *path, t_env *env);
void	re_pwd(char *path, t_env *env);
char	*extract_value(char *equal_pos);
//end builtins
#endif