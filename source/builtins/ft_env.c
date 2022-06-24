#include "../includes/minishell.h"

void	ft_env()
{
	t_list	*tmp;

	tmp = gen->env;
	if (tmp->content)
	{
		while (tmp)
		{
			if (ft_strchr((char *)tmp->content, '='))
				ft_putendl_fd((char *)tmp->content, 1);
			tmp = tmp->next;
		}
	}
	return ;
}