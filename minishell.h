/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:40:38 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/09/26 15:39:39 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
// libs
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

typedef enum e_type
{
	WORD,
	R_IN,
	R_OUT,
	APP,
	HER,
	PIPE
}	t_e_type;

// Token structure
typedef struct s_token
{
	char			*str;
	t_e_type		tokenType;
	struct s_token	*next;
	// struct s_token	*previous;
}	t_token;

// Redirection structure
typedef struct s_redir
{
	char			*filename;
	t_e_type		type;
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
// end of parsing funcs

// utils
int		ft_strlen(char	*str);
char	**ft_split(char *s, char c);
char	*ft_strtrim(char const *s1, char const *set);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(char *s1);

#endif