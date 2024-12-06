/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:40:38 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/05 17:22:24 by ayhamdou         ###   ########.fr       */
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
# include <fcntl.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

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
}	t_token;

// Redirection structure
typedef struct s_redir
{
	char			*filename;
	int				flag_in;
	int				flag_out;
	int				fd;
	int				is_open;
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

// parsing funcs
int		parser(char *user_inp, t_env *ev);
void	handle_word(t_command **command, char *str, int *argcount);
void	handle_redirections(t_command *command, t_token **token_list);
void	tokenizer(char *user_inp, t_token **tokenList);
void	create_token(t_token **token, char *data, t_etype type, t_etype qt);
void	expander(t_token **tokens, t_env *ev);
void	expand_it(char *str, char **res, char **expanded, t_env *ev);
char	*ret_env(char *str, int *i, t_env *ev);
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
// end of parsing func

// cleaners
void	clean_tokens(t_token **tokens);
void	clean_cmds(t_command **cmds);
void	clean_red(t_redir **reds);

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
void	rm_qt(char **str, int inextarction);

//temp
void 	printtokens(t_token *lst);
void	printredirections(t_redir *lst);
void	printcommnads(t_command *lst);
char	*gettype(t_etype type);
void	exit_funcs(void);

//thats
//builtins
void	the_echo(t_command *cmd);
//end temp
#endif