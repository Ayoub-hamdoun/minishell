/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallali <rallali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:40:38 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/10/14 21:03:39 by rallali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libc.h"
#include <readline/readline.h>
#include <readline/history.h>


// Enum declaration
typedef enum e_type
{
    WORD,
    R_IN,
    R_OUT,
    APP,
    HER
} e_type;

// Token structure
typedef struct s_env
{
    char *key;
    char *value;  
    struct s_env *next;
} t_env;

typedef struct s_token
{
    char *str;
    e_type token;
    struct s_token *next;
} t_token;

// Redirection structure
typedef struct s_redir
{
    char *filename;
    e_type type; // Changed e_num to e_type
    struct s_redir *next; // Fix the next pointer to s_redir
} t_redir;

// Command structure
typedef struct s_command
{
    char **args;
    char **env;
    struct s_redir *rederects; // Fix the pointer to s_redir
    int is_builtin;
    struct s_command *next; // Fix the next pointer to s_command
} t_command;


int	ft_strncmp(const char*s1, const char *s2, int n);
char	**ft_split(char const *s, char c);
void the_cd(t_command *cmd , t_env *env);
void the_pwd();
void update_oldpwd(char *path,t_env *env);
void re_pwd(char *path, t_env *env);
void the_unset(t_command *cmd ,t_env **env);
void the_echo(t_command *cmd);
void the_export(t_command *cmd, t_env **env);
int check_equal(char *cmd );
char *ft_strjoin(char *str, char *str1);
int check_equal(char *cmd);
#endif
