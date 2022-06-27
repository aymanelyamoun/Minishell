#include "../includes/minishell.h"

t_list *swap(t_list *ptr1, t_list *ptr2)
{
    t_list *tmp = ptr2->next;
    ptr2->next = ptr1;
    ptr1->next = tmp;
    return (ptr2);
}

void bubbleSort(t_list **head, int count)
{
    t_list **h; 
    t_list *p1;
    t_list *p2;
    int index1;
    int index2;
    int swapped;

    for (index1 = 0; index1 <= count; index1++)
    {
        h = head;
        swapped = 0;

        for (index2 = 0; index2 < count - index1 - 1; index2++)
        {
            p1 = *h;
            p2 = p1->next;
            if (((char *)p1->content)[0] > ((char *)p2->content)[0])
            {
                *h = swap(p1, p2);
                swapped = 1;
            }

            h = &(*h)->next;
        }
        if (swapped == 0)
            break;
    }
}

int len_list(t_list **list)
{
    t_list *tmp;
    int index;

    index = 0;
    tmp = *list;
    while (tmp)
    {
        tmp = tmp->next;
        index++;
    }
    return (index);
}

void ft_sort (t_gen *gen)
{
    bubbleSort(&(gen)->env, len_list(&(gen)->env));
    print_export((gen)->env);
}

void	print_export(t_list *env)
{
	int		index;
	char	**split;

	index = 0;

    if(!env)
        return ;
    while (env && env->content)
    {
        if (!ft_strchr(((char *)env->content), '='))
        {
            ft_putstr_fd("declare -x ", 1);
            ft_putstr_fd((char *)env->content, 1);
            ft_putchar_fd('\n', 1);
        }
        else
        {
            split = ft_split(env->content, '=');
            ft_putstr_fd("declare -x ", 1);
            ft_putstr_fd(split[0], 1);
            ft_putstr_fd("=", 1);
            if (split[1])
            {
                if(split[0])
                    ft_putstr_fd("\"", 1);
                ft_putstr_fd(split[1], 1);
                if(split[0])
                    ft_putstr_fd("\"", 1);
            }
            else
                ft_putstr_fd("\"\"", 1);
            ft_putchar_fd('\n', 1);
        }
        env = env->next;
    }
    free_split(split);
}

void	free_split(char **array)
{
	int	index;

	index = 0;
	while (array[index])
	{
		free(array[index]);
		index++;
	}
	free(array);
}


int ft_export(char **next)
{
    int index;
    char	**split;
    char *str;

    if (!gen.env)
        return (0);
    if (ft_strlen2(next) == 1)
    {
        ft_sort(&gen);
        return (0);
    }
    index = 1;
    if(find_plus(next[index]) >= 1)
	{
		append_case(&gen.env, next[index]);
        ft_putchar_fd('1', 1);
		return (0);
	}
    while (next[index])
    {
        if (check_arg(next[index]))
        {
            print_err_exp(next[index]);
        }
        else if (!ft_add_list(&gen.env, next[index]))
            ft_lstadd_back(&gen.env, ft_lstnew(ft_strdup(next[index])));
        index++;
    }
    return (0);
}
