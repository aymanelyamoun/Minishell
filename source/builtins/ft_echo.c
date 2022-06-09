#include "../includes/minishell.h"

// int ft_echo(int argc, char **argv)
// {
//     int index;
//     int flag;

//     index = 0;
//     flag = 1;

//     while(++index < argc)
//     {
//         if(is_flag(argv[index]))
//             flag == 0;
//         else
//         {
//             printf("%s", argv[index]);
//             if(index < argc - 1)
//                 printf(" ");
//         }
//     }
//     if(flag == 1)
//         ft_putchar_fd('\n', 1);
//     return (0);
// }


// int	is_flag(char *str)
// {
// 	int	index;

// 	index = 0;
// 	if (str[0] != '-' || str[1] != 'n')
// 		return (0);
// 	while (str[index] && str[index] == 'n')
// 		index += 1;
// 	if (str[index])
// 		return (0);
// 	return (1);
// }
   