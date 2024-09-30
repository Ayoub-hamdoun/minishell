#include "../minishell.h"

char *get_home(char **env, char *s)
{
    int i = 0;
    while (env[i])
    {
        if (strncmp(env[i],s,strlen (s)) == 0)
            return (env[i] + strlen (s));
        i++;
    }
    return (NULL);
}

void update_env(char **env)
{
    int i = 0;
    char *old_pwd = NULL;
    char *new_pwd = getcwd(NULL, 0);

    if (!new_pwd)
        return;
    while (env[i])
    {
        if (strncmp(env[i], "PWD=", 4) == 0)
        {
            old_pwd = strdup(env[i] + 4);
            break;
        }
        i++;
    }
    i = 0;
    while (env[i])
    {
        if (strncmp(env[i], "OLDPWD=", 7) == 0 && old_pwd)
        {
            free(env[i]);
            env[i] = malloc(strlen("OLDPWD=") + strlen(old_pwd) + 1);
            if (!env[i])
            {
                free(new_pwd);
                free(old_pwd);
                return;
            }
            strcpy(env[i], "OLDPWD=");
            strcat(env[i], old_pwd);
        }
        if (strncmp(env[i], "PWD=", 4) == 0)
        {
            free(env[i]);
            env[i] = malloc(strlen("PWD=") + strlen(new_pwd) + 1);
            if (!env[i])
            {
                free(new_pwd);
                free(old_pwd);
                return;
            }
            strcpy(env[i], "PWD=");
            strcat(env[i], new_pwd);
        }
        i++;
    }
    free(new_pwd);
    free(old_pwd);
}



void do_cd(t_command *cmd, char **env)
{
    char *home = NULL;

    if (cmd->args[1])
    {
        if (cmd->args[1][0] == '-')
        {
            home = get_home(env, "OLDPWD=");
            if (home)
            {
                if (chdir(home) != 0)
                {
                    perror("chdir");
                }
            }
            else
            {
                printf("OLDPWD not set\n");
            }
        }
        else if (chdir(cmd->args[1]) != 0)
        {
            perror("chdir");
        }
    }
    else if(!cmd -> args[1])
    {
        home = get_home(env,"HOME=");
        if (home)
            {
            if (chdir(home) != 0)
                perror("chdir");
            }
    }
}