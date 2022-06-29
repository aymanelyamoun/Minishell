#include "../includes/minishell.h"

//TODO:exit is fucked

int ft_exit(char **next)
{
    if(ft_strlen2(next) == 1)
    {
        ft_putstr_fd("exit\n", 2);
        gen.exit_status = ft_atoll(*next);
    }
    if(ft_strlen2(next) == 2)
    {
        if(check_valid(*(next + 1)) == 0)
        {
            ft_putstr_fd("Minishell : exit : ", 2); //in one function
            ft_putstr_fd(next[1], 2);
            ft_putstr_fd("numeric argument required\n", 2);
            gen.exit_status = 255;
        }
        else if(check_valid(*(next + 1)) == 1)
            gen.exit_status = ft_atoll(next[1]);
    }
    if(ft_strlen2(next) > 2)
    {
        ft_putstr_fd("exit\n", 2);
        ft_putstr_fd("exit : too many arguments\n", 2);
        gen.exit_status = 255;
    }
    exit(gen.exit_status);
    free_split(next);
    return (0);
}

int is_long(char *next)
{
    if(ft_atoll(next) > 2147483647 || ft_atoll(next) <  -2147483648)
            return (1);
    return (0);
}

int check_valid(char *next)
{
    int index;

    index = 0;
    // printf("----- %s\n", next);
    while(next[index])
    {
        if(ft_isdigit(next[index]) != 1)
        {
            if((next[index] == '+' || next[index] == '-') && index == 0)
            {
                index++;
                continue;
            }
            return (0);
        }
        index++;
    }
    return (1);
}
