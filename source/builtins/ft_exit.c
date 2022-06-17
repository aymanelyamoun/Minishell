#include "../includes/minishell.h"

// int ft_exit(t_list **env, char **arg)
// {
//     int exit_num;

//     rl_clear_history();
//     free_env(env);
//     ft_putstr_fd("exit\n", 1);
//     exit_num = convert(arg[1]);
//     printf("%d", exit_num);
//     exit(exit_num);
// }


// int convert(char *arg)
// {
//     int exit_num;

//     if (arg == NULL)
//         exit_num = 0;
//     else
//         exit_num = ft_atoi(arg);
//     return (exit_num);
// }