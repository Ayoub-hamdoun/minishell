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
char **get_copy(char **ev)
{
    int i = 0;
    int k = 0;
    
    while (ev[i])
        i++;
    
    char **env_copy = malloc(sizeof(char *) * (i + 1));
    if (!env_copy)
        return NULL;
    
    while (k < i)
    {
        env_copy[k] = strdup(ev[k]);
        if (!env_copy[k])
        {
            free_env(env_copy);
            return NULL;
        }
        k++;
    }
    env_copy[k] = NULL;
    
    return env_copy;
}
void print_env(char **env)
{
    int i = 0;
    int j = 0;

    while (env[i])
    {
        j = 0;
        while (env[i][j])
        {
            printf("%c", env[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
}

void start(char **ev) 
{
    t_command *cmd = malloc(sizeof(t_command));
    char *input = NULL;
    char **env_copy=get_copy(ev);
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
        {
         update_env(env_copy);
            do_cd(cmd,env_copy);
        }
        else if (strncmp (cmd ->args[0],"pwd",3)==0)
            do_pwd();
        else if (strncmp(cmd ->args[0],"env",3) == 0)
            print_env(env_copy);
        else if(strncmp(cmd ->args[0],"echo",4) == 0)
            do_echo(cmd);
        else if (strncmp(cmd ->args[0],"unset",5) == 0)
            unset(cmd ,env_copy);
        else if (strncmp (cmd ->args[0],"export",6) == 0)
            do_export(cmd,&env_copy);
        // else if (strncmp(cmd ->args[0],"exit",4) == 0)
        //     shut_down(cmd);
        free(input);
    }
    free(cmd);
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