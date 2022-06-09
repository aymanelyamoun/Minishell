#include "../includes/minishell.h"

void	ft_env(t_list *env)
{
	t_list	*tmp;

	tmp = env;
	if (tmp->content)
	{
		while (tmp)
		{
			if (ft_strchr((char *)tmp->content, '='))
				ft_putendl_fd((char *)tmp->content, 1);
			tmp = tmp->next;
		}
	}
}