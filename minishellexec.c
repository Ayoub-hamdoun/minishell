#include "minishell.h"

void fill(char *av, t_command *cmd)
{
    if (!av)
        return;
    char **args = ft_split(av, ' ');

    if (!args)
        return;
    int i = 0;

    while (args[i]) 
        i++;

    cmd->args = malloc(sizeof(char *) * (i + 1));
    if (!cmd->args)
    {
        free(args);
        return;
    }

    int j = 0;
    while (j < i)
    {
        cmd->args[j] = args[j];
        j++;
    }
    cmd->args[j] = NULL;
    free(args);
}

void get_env(t_env *env, char **ev)
{
    int i = 0;
    char *sign;

    if (!env || !*ev)
        return ;

    while (ev[i])
    {
        sign = strchr(ev[i], '=');
        
        if (sign)
        {
            env->key = strndup(ev[i], sign  - ev[i]);
            env->value = strdup(sign + 1);
        }
        else
        {
            env->key = strdup(ev[i]);
            env->value = NULL;
        }
        if (ev[i + 1])
        {
            env->next = malloc(sizeof(t_env));
            env = env->next;
        }
        else
            env->next = NULL;
        i++;
    }
}
void print_env(t_command *cmd, t_env *env)
{
    int i;
    while (env)
    {
        i = 0;
        while (cmd->args[i])
        {
            if (env->key && env->value)
            {
                if (check_equal(cmd->args[i]) == 1)
                {
                    printf("%s=%s\n", env->key, env->value);
                }
            }
            else if (env->key)
                {
                     if (check_equal(cmd->args[i]) == 0)
                        printf("%s\n", env->key); 
                }
            i++;
        }
        env = env->next;
    }
}



void start(char **ev) 
{
     char *input = NULL;
    t_command *cmd = malloc(sizeof(t_command));
    t_env *env = malloc(sizeof(t_env));

    if (!env)
        return;

    get_env(env, ev);
        // printf("%s\n", env->value);

    while (1) 
    {
        input = readline("minishell> ");
        if (!input)
            break;
        if (!*input)
            continue ;
        add_history(input);
        fill(input, cmd);
        if (!cmd->args[0])
            return;
        if (strncmp(cmd->args[0], "cd", 2) == 0)
            the_cd(cmd,env);
        else if (strncmp (cmd ->args[0],"pwd",3) == 0)
            the_pwd();
        else if (strncmp(cmd ->args[0],"env",3) == 0)
            print_env(cmd ,env);
        else if (strncmp(cmd ->args[0],"unset",5) == 0)
            the_unset(cmd ,&env);
        else if(strncmp(cmd ->args[0],"echo",4) == 0)
            the_echo(cmd);
        else if (strncmp (cmd ->args[0],"export",6) == 0)
            the_export(cmd,&env);
    }
        // else if (strncmp(cmd ->args[0],"exit",4) == 0)
        //     shut_down(cmd);
    //     free(input);
    // }
    // free(cmd);
}
int main(int ac , char **av , char **ev) 
{
    if (ac == 0)
        return (0);
    (void)av;
    if (!*ev)
        return 0;
        // add the default envirement
    else
        start(ev);
    return 0;
}