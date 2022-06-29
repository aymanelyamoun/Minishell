#include "../includes/minishell.h"


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

int ft_export(char **next)
{
    int index;

    if (!gen.env)
        return (0);
    if (ft_strlen2(next) == 1)
    {
        ft_sort(&gen);
        return (0);
    }
    index = 1;
    while (next[index])
    {
        if (check_arg(next[index]))   //handeling += ?
        {
            print_err_exp(next[index]);
        }
        else if (!ft_add_list(&gen.env, next[index]))
            ft_lstadd_back(&gen.env, ft_lstnew(ft_strdup(next[index])));
        index++;
    }
	free_split(next);
    return (0);
}


