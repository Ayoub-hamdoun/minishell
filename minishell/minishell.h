/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallali <rallali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:40:38 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/09/30 00:58:24 by rallali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
char **var_env(char **env);
void print_env(char **env);
void do_pwd();
void do_cd();
void do_echo(t_command *cmd);
void do_export(t_command *cmd,char ***env);
void free_env(char **env);
void unset(t_command *cmd,char **env_copy);
void shut_down(t_command *cmd);
char *do_newpwd(char *path);
void update_env(char **env);
char **get_copy(char **ev);
int check_equal(char *args);
int after_equal(char *args);
#endif
