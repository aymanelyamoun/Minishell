#include "../includes/minishell.h"
//should handle the incremented value inside env, and split it by result by =


t_list *env_create(char **envp)
{
    t_list *tmp = NULL;
    t_list *head;
    char *s;
    int index;

    index = 1;
    if(!(**envp) || !(envp) || !(envp[0]))
    {
        head = ft_lstnew(NULL);
        return (head);
    }
    s = ft_strdup(envp[0]);
    head = ft_lstnew(s);
    ft_lstadd_back(&head, tmp);
    while(envp[index])
    {
        s = ft_strdup(envp[index]);
        tmp = ft_lstnew(s);
        ft_lstadd_back(&head, tmp);
        index++;
    }
    return (head);
}

// char **set_env(char **envp)
// {
//     int index;
//     char **tmp;

//     if(envp)
//     {
//         index = 0;
//         while(envp[index])
//             index++;
//     }
//     tmp = malloc(sizeof(char *) * (index + 1));
//     if (!tmp)
//         return (NULL);
//     index = 0;
//     while(envp[index])
//     {
//         tmp[index] = ft_strdup(envp[index]);
//         index++;
//     }
//     tmp[index] = NULL;
//     return (tmp);
// // }