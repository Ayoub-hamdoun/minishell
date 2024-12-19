/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:17:58 by rallali           #+#    #+#             */
/*   Updated: 2024/12/19 17:17:01 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


void remove_env_var(t_env **env, const char *key)
{
    t_env *current = *env;
    t_env *prev = NULL;
    t_env *temp;

    while (current)
    {
        if (strcmp(current->key, key) == 0 && ft_strcmp(current->key, "_") != 0)
        {
            temp = current;
            if (prev)
                prev->next = current->next;
            else
                *env = current->next;
            free(temp->key);
            free(temp->value);
            free(temp);
            return;
        }
        prev = current;
        current = current->next;
    }
}

int check_param(char *str)
{
    int i;

    if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
        return (1);
    i = 1;
    while (str[i])
    {
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return (1);
        i++;
    }
    return (0);
}

int the_unset(t_command *cmd, t_env **env)
{
    int i;

    if (!cmd->args[1])
        return (0);
    i = 1;
    while (cmd->args[i])
    {
        if (check_param(cmd->args[i]))
        {
            ft_putstr_fd("unset: `", 2);
            ft_putstr_fd(cmd->args[i], 2);
            ft_putstr_fd("': not a valid identifier\n", 2);
        }
        else
            remove_env_var(env, cmd->args[i]);
        i++;
    }
    return (0);
}
