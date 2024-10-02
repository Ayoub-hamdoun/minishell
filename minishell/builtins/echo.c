#include "../minishell.h"

int count_n(char *cmd)
{
    int i = 1;
    if (cmd[0] == '-')
    {
        while (cmd[i] == 'n')
            i++;
        if (cmd[i] == '\0')
            return (0);
    }
    return (1);
}

void do_echo(t_command *cmd)
{
    if (!cmd->args[1])
    {
        printf("\n");
        return;
    }
    
    int count = 0;
    int i = 1;
    while (cmd->args[i] && count_n(cmd->args[i]) == 0)
    {
        count = 1;
        i++;
    }
    while (cmd->args[i])
    {
        printf("%s", cmd->args[i]);
        if (cmd->args[i + 1])
            printf(" "); 
        i++;
    }

    if (count == 0)
        printf("\n");
}
