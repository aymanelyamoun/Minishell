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
    else if(ft_strlen(next) == 2)
    {
        if(!check_num(next[1]) || !check_range(next[index]))
        {
            ft_putstr_fd("Minishell : exit : ", 2);
            ft_putstr_fd(next[index], 2);
            ft_putstr_fd("numeric argument required\n", 2);
            gen->exit_status = 255;
            free_env(&gen->env);
            exit((int)gen->exit_status);
        }
        else
            // modulo 256?

    }
    else
    {
        ft_putstr_fd("Minishell: exit : too many arguments\n", 2);
        return (1);
    }
    free_env(&gen->env);
    exit((int)gen->env);
}
