#include "../minishell.h"

void declare_x(char **env)
{
    char *declare = "declare -x ";
    int i = 0;
    int len;
    char *hold = NULL;
    
    while (env[i])
    {
        len = strlen(env[i]);
        hold = malloc(len + 1);
        if (hold == NULL)
            return;
        strcpy(hold, env[i]);
        
        free(env[i]);
        env[i] = malloc(strlen(declare) + len + 1);
        if (env[i] == NULL)
        {
            free(hold);
            return;
        }
        strcpy(env[i], declare);
        strcat(env[i], hold);
        
        free(hold);
        i++;
    }
    env[i] = NULL;
}
void free_env(char **env)
{
    int i = 0;
    while (env[i])
    {
        free(env[i]);
        i++;
    }
    free(env);
}
char **get_coppy(char **ev, int j,char *s)
{
    int i = 0;
    int k = 0;
    
    while (ev[i])
        i++;
    char **env_copy = malloc(sizeof(char *) * (i + j + 1));
    if (!env_copy)
        return NULL;
    while (k < i)
    {
        env_copy[k] = strdup(ev[k]);
        if (!env_copy[k])
            // free_env(env_copy);
            env_copy[k]  = strdup(s);
            // return NULL;
        k++;
    }
   
    env_copy[k + 1] = NULL;
    
    return env_copy;
}
void add_var(char *args, char ***env)
{
    char **hold;
    int i = 0;
    // if (*env && **env && ***env)
    //     return ;
    hold = get_coppy(*env, 1,args);
    if (!hold)
    {
        printf("Error: Memory allocation failed in add_var.\n");
        return;
    }

    free_env(*env);

    while (hold[i])
        i++;
    
    hold[i - 1 ] = strdup(args);
    
    hold[i] = NULL;
    *env = hold;
}
int is_valid (t_command *cmd)
{
    int i = 1;

    while (cmd ->args[i])
    {
        if (!((cmd ->args[i][0] >= 'a' && cmd ->args[1][0] <= 'z') || (cmd ->args[1][0] >= 'A' && cmd ->args[1][0] <= 'Z')))
            return (1);
        i++;
    }
        return (0);
}
int check_equal(char *args)
{

    int i = 0;
    while (args[i] && args[i] != '=')
        i++;
    if (args[i] == '=')
        return (1);
    return (0);
}
int after_equal(char *args)
{
    int i = 0;
    while (args[i])
    {
        if (args[i] == '=')
        {
            if (args[i+1] == '\0' || args[i + 1] == '\n')
                return (1);
        }
        i++;
    }
    return (0);
}
void do_export(t_command *cmd, char ***env)
{
    if (!cmd->args[1])
    {
        char **ev = get_copy(*env);
        declare_x(ev); 
        print_env(ev);
    }
    else
    {
        if (is_valid(cmd))
            perror("export");
        int i = 1;
        int j;
        while (cmd ->args[i])
        {
        j = 0;
            while (strncmp(cmd ->args[i],env[j],strlen(cmd ->args[i])))
            {
            unset
            add_var(cmd ->args[i], env);
            j++;
            }
                i++;
        }
    }
}
