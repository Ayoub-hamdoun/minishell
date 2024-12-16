/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:25:30 by rallali           #+#    #+#             */
/*   Updated: 2024/12/16 20:53:30 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//the variable can be appended even if no cmd already their done
//even if there is an error you should set the error then continue on setting the other variables done
// if the variable was without = and we want to append it segfault  done
void declare_x(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if ((tmp->key && tmp->value))
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		else if (tmp->key)
			printf("declare -x %s\n", tmp->key);
		tmp = tmp->next;
	}
}
int check_equal(char *cmd)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '=')
			return (1);
		i++;
	}
	return (0);
}
int ft_integer(char *cmd)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] < '0' || cmd[i] > '9')
			return (0);
		i++;
	}
	return (1);
}
int ft_is_alpha(char *cmd)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if ((cmd[i] < 'A' || (cmd[i] > 'Z' && cmd[i] < 'a') || cmd[i] > 'z') && (cmd[i] != '_'))
			return (0);
		i++;
	}
	return (1);
}
int check_until_equal(char *cmd)
{
	int i;

	i = 0;
	while (cmd[i] != '=')
	{
	    if (!((cmd[i] >= 'A' && cmd[i] <= 'Z') || 
              (cmd[i] >= 'a' && cmd[i] <= 'z') || 
              (cmd[i] >= '0' && cmd[i] <= '9') || 
            cmd[i] == '_' || cmd[i] == '+'))
        {
            printf(" utils equal export: `%s': not a valid identifier\n", cmd);
            return (1);
        }
		i++;
	}
	return (0);
}
int check_without_equal(char *cmd)
{
    int i;

    i = 0;
    while (cmd[i])
    {
        if (!((cmd[i] >= 'A' && cmd[i] <= 'Z') || 
              (cmd[i] >= 'a' && cmd[i] <= 'z') || 
              (cmd[i] >= '0' && cmd[i] <= '9') || 
              cmd[i] == '_'))
        {
            printf("without equal export: `%s': not a valid identifier\n", cmd);
            return (1);
        }
        i++;
    }
    return (0);
}


int check_valid (char *cmd)
{
	// int i;
	int flag;
	
	// i = 0;
	if (cmd[0] == '-')
		{
			printf("export: -%s: invalid option\n", cmd);
			printf("export: usage: export [name[=value] ...] or export -p\n");
			return (1);
		}
	if ((cmd [0] < 'A' || (cmd [0] > 'Z' && cmd [0] < 'a') || cmd [0] > 'z') && (cmd[0] != '_'))
	{
		printf("export: `%s': not a valid identifier\n", cmd);
		return (1);
	}
	if (check_equal(cmd) == 1)
		flag = check_until_equal(cmd);
	else
		flag = check_without_equal(cmd);
	if (flag == 1 )
		return (1);
	return (0);
}

char *extract_value(char *cmd)
{
    int i = 0;

    while (cmd[i])
    {
        if (cmd[i] == '=')
            return (strdup(cmd + i + 1));
        i++;
    }
    return (NULL);
}
char *extract_key(char *cmd)
{
    int i = 0;

    while (cmd[i] && cmd[i] != '=' && cmd[i] != '+')
        i++;

	char *n = strndup(cmd, i);
	add(n);
    return (n);
}


int check_duplicate(char *cmd, t_env **env)
{
	t_env *current = *env;
	char *key = extract_key(cmd);

	while (current)
	{
		if (current->key && strcmp(current->key, key) == 0)
			return (0);
		current = current->next;
	}
	return (1);
}
void change_value(char *cmd, t_env **env)
{
	t_env *current = *env;
	char *key = extract_key(cmd);
	char *value = extract_value(cmd);

	while (current)
	{
		if (current->key && strcmp(current->key, key) == 0)
		{
			//free(current->value);
			current->value = value;
			return ;
		}
		current = current->next;
	}
}
void add_variable(char *cmd, t_env **env)
{
    t_env *current = *env;
    t_env *new;
    char *key = extract_key(cmd);
    char *value = extract_value(cmd);
    if (key == NULL)
        return;

    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            // if (current->value != NULL)
                //free(current->value);
            if (value != NULL)
                current->value = strdup(value);
            else
                current->value = NULL;
            free(key);
            return;
        }
        if (current->next == NULL)
            break;
        current = current->next;
    }
    new = ft_malloc(sizeof(t_env));
    if (new == NULL)
        return;

    new->key = key;
    if (value != NULL)
        new->value = strdup(value);
    else
        new->value = NULL;
    new->next = NULL;
    if (current == NULL)
        *env = new;
    else
        current->next = new;
}

void add_var(char *cmd, t_env **env)
{
	if (check_duplicate(cmd, env) == 0)
		change_value(cmd, env);
	else if (check_duplicate(cmd, env) == 1)
		add_variable(cmd, env);
}

int duplicate_sign(char *cmd)
{
	int i;
	int flag = 0;
	i = 0;
	
	while (cmd[i])
	{
		if (cmd[i] == '+')
			flag++;
		i++;
	}
	if (flag > 1)
		return (1);
	else if (flag == 0)
		return (2);
	return (0);
}
int check_plus(char *cmd,int flag)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if ((duplicate_sign(cmd) == 1) && flag == 0)
		{
			printf("export: `%s': not a valid identifier\n", cmd);
			return (1);
		}
		else if ((duplicate_sign(cmd) == 2))
			return (2);
		i++;
	}
	return (0);
}

void join_var(char *cmd, t_env **env)
{
	t_env *current = *env;
	char *key = extract_key(cmd);
	char *value = extract_value(cmd);
	char *tmp;
	
	while (current)
	{
		if (current->key && strcmp(current->key, key) == 0)
		{
			tmp = current->value;
			if (current->value == NULL)
				current->value = value;
			else
				current->value = ft_strjoin(current ->value, value);
			free(tmp);
			return ;
		}
		current = current->next;
	}
}
void the_export(t_command *cmd, t_env **env)
{
	int	i;
	int flag;
	i = 1;

	if (!cmd->args[i])
	{
		declare_x(env);
		return ;
	}
	while (cmd -> args[i])
	{
		if (check_valid(cmd -> args[i]) == 1)
			flag = 1;
		else
		{
			if (check_equal(cmd -> args[i]) == 1)
			{
				if (check_plus(cmd -> args[i],0) == 0)
				{
					if (check_duplicate(cmd -> args[i], env) == 1)
						add_variable(cmd -> args[i], env);
					else
						join_var(cmd -> args[i], env);
				}
				else if (check_plus(cmd -> args[i],1) == 2)
					add_var(cmd->args[i], env);
			}
			else
			{
			if (check_duplicate(cmd -> args[i], env) == 1)
					add_variable(cmd -> args[i], env);
			}
		}
		i++;
	}
	if (flag == i)
		return ;
}
