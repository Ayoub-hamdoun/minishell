#include "minishell.h"

int exit_status(int status)
{
    static int es;

    if (status != -1)
        es = status;
    return (es);
}