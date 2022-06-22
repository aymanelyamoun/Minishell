#include "../includes/minishell.h"

// int ft_unset(t_gen *gen, char **next)
// {
//     int index;

//     if (!gen->env)
//         return (0);
//     if (ft_strlen2(next) == 1)
//         return (0);
//     index = 1;
//     while (next[index])
//     {
//         if (check_arg2(next[index]))
//         {
//             print_err_exp(next[index]);
//             gen->exit_status = 1;
//         }
//         else
//         {
//            start_unset(gen->env, next[index]);
//            gen->exit_status = 0;
//         }
//         index++;
//     }
//     return (0);
// }

// int check_arg2(char *next)
// {
//     int	index;

// 	index = 0;
// 	if (!next)
// 		return (0);
// 	if (!next[index] || (!ft_isalpha(next[index]) && next[index] != '_'))
// 		return (1);
// 	index++;
// 	while (next[index])
// 	{
// 		if ((next[index] != '_' && !ft_isalnum(next[index])))
// 			return (1);
// 		index++;
// 	}
// 	return (0);
// }


// int start_unset(t_list *env, char *next)
// {
//     size_t len;
//     t_list *bef;
//     t_list *tmp;

//     len = ft_strlen(next);
//     tmp = env;
//     bef = (t_list *) NULL;
//     while(tmp)
//     {
//         if(!ft_strncmp((char *)tmp->content, next, len))
//             break ;
//         bef = tmp;
//         tmp = tmp->next;
//     }
//     if (tmp)
//     {
//         if(bef)
//             bef->next = tmp->next;
//         else
//             env = tmp->next;
//         free(tmp->content);
//         free(tmp);
//     }
//     return (0);
// }