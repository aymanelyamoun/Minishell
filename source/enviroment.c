#include "../includes/minishell.h"


//should handle the incremented value inside env, and split it by result by =

char **set_env(char **envp)
{
    int index;
    char **tmp;

    if(envp)
    {
        index = 0;
        while(envp[index])
            index++;
    }
    tmp = malloc(sizeof(char *) * (index + 1));
    if (!tmp)
        return (NULL);
    index = 0;
    while(envp[index])
    {
        tmp[index] = ft_strdup(envp[index]);
        index++;
    }
    tmp[index] = NULL;
    return (tmp);
}