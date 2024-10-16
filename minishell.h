/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:40:38 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/10/16 10:19:34 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
// libs
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

typedef enum type
{
	WORD,
	R_IN,
	R_OUT,
	APP,
	HER,
	PIPE
}	t_etype;

// Token structure
typedef struct s_token
{
	char			*str;
	t_etype			tokenType;
	struct s_token	*next;
}	t_token;

// Redirection structure
typedef struct s_redir
{
	char			*filename;
	t_etype			type;
	struct s_redir	*next;
}	t_redir;

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

// end of parsing funcs

// utils
int		ft_strlen(char	*str);
char	**ft_split(char *s, char c);
char	*ft_strtrim(char *s1, char *set);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(char *s1);
char	*ft_substr(char *s, int start, int len);

//temp
void printtokens(t_token *lst);
//end temp

#endif