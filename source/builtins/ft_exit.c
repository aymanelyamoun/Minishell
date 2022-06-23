#include "../includes/minishell.h"

int ft_exit(char **next)
{
    int index;

    if(ft_strlen2(next) == 1)
    {
        free_env(&gen->env);
        ft_putstr_fd("exit\n", 2);
        exit(0);
    }
    return (0);
}
