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
        {
            gen.exit_status = ft_atoll(next[1]);
        }
    }
    if(ft_strlen2(next) > 2)
    {
        ft_putstr_fd("exit\n", 2);
        ft_putstr_fd("exit : too many arguments\n", 2);
        gen.exit_status = 255;
    }
    exit(gen.exit_status);
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

//if the exit status is negative , return 256 - (num)
//If the exit code is a negative number, the resulting exit status is that number subtracted from 256.
//check_num(next[1]) || check_range(next[1])
            // if(is_long(next[index]) == 1 && ft_atoll(next[index]) < 0) //=?
            //     gen.exit_status = (ft_atoll(next[index]) | 1) % 256;
            // if(is_long(next[index]) == 1 && ft_atoll(next[index]) > 0) //=?
            //     gen.exit_status = (ft_atoll(next[index])) % 256;
            // else if(is_long(next[index]) == 0 && ft_atoll(next[index]) > 0 && ft_atoll(next[index]) > 256)
            //     gen.exit_status = ft_atoll(next[index]) % 256;
            // else if(is_long(next[index]) == 0 && ft_atoll(next[index]) > 0 && ft_atoll(next[index]) < 256)
            //      gen.exit_status = ft_atoll(next[index]);
            // else if(is_long(next[index]) == 0 && ft_atoll(next[index]) < 0)
            //     gen.exit_status = (256 + ft_atoll(next[index]));
// int check_long(char *next)
// {
//     int index;

//     index = 0;
//     while(next[index])
//     {
//         if(ft_atoll(next[index]) != 0)
//         {
//             return (0);
//         }
//         index++;
//     }
//     return (1);
// }




//check the numbers of arguments : if it none : exit(0)
//if there are two arguments, check the second one
//-------------------->not digit = error
//-------------------->if digit
//=====================    |
//---------------------> is it short and negative? = exit(256 - number)
//--------------------->is it long ?
//=====================>    | 
//----------------------> is it long and negative ? = exit(256 - long)
//---------------------->is it long and positive ? = exit (num % 256)
//----------------------> more then an arg ? => error
//----------------------> else aka short (exit(num))

//take the arg as long anyways