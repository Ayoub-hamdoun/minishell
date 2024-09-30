#include "../minishell.h"
void swipe_up(char **env_copy,int i)
{
    while(env_copy[i])
    {
        env_copy[i] = env_copy[i + 1];
        i++;
    }
}
void unset(t_command *cmd,char **env_copy)
{
    int i = 0;

    while (env_copy[i])
    {
        if (ft_strncmp(cmd ->args[1],env_copy[i],strlen (cmd ->args[1])) == 0)
        {
            free(env_copy[i]);
            swipe_up(env_copy,i);
        }
        i++;
    }

}