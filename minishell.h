/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:40:38 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/01 19:33:53 by ayhamdou         ###   ########.fr       */
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
	char	*str;
	t_etype	tokenType;
	t_etype	q_type;		// type of the quote, needed for expanding purpose
	struct s_token	*next;
}	t_token;

// Redirection structure
typedef struct s_redir
{
	char			*filename;
	int				flag_in;
	int				flag_out;
	t_etype			type;
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

// parsing funcs
int		parser(char *userInp);
void	tokenizer(char *userInp, t_token **tokenList);
void	expander(t_token **tokens);
// end of parsing func


// cleaners
void	clean_tokens(t_token **tokens);

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

//lexer
void lexer(t_token *tokens);
void check_quotes_alt(t_token *token);
//end temp
void check_last_out(t_command *token);
void check_last(t_command *token);
void	ft_getenv(t_env *env, char **ev);
#endif