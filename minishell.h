/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:40:38 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/09/24 11:50:10 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// utils
char	**ft_split(char *s, char c);

// parsing funcs

typedef enum e_type
{
	WORD,
	R_IN,
	R_OUT,
	APP,
	HER,
	PIP
}	e_type;

// Token structure
typedef struct s_token
{
	char			str;
	e_type			token;
	struct s_token	*next;
}	t_token;

// Redirection structure
typedef struct s_redir
{
	char			filename;
	e_type			type; // Changed e_num to e_type
	struct s_redir	*next; // Fix the next pointer to s_redir
}	t_redir;

// Command structure
typedef struct s_command
{
	char				*args;
	int					is_builtin;
	struct s_redir		*rederects; // Fix the pointer to s_redir
	struct s_command	*next; // Fix the next pointer to s_command
}	t_command;


void	parser(char *userInp);
// end of parsing funcs