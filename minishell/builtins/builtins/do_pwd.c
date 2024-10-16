#include "../minishell.h"

void do_pwd()
{
    char *path;
    
    path = getcwd(NULL, 0); 
    if (!path)
    {
        perror("pwd");
        return;
    }

    printf("%s\n", path);
    // update_env(env_copy,path);
    free(path);
}