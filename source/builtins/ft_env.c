#include "../includes/minishell.h"

void	ft_env(char **str)
{
	t_list	*tmp;
	int		index;

	index = 0;
	if (str[1])
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(str[1], 2);
		ft_putstr_fd(" : No such file or directory\n", 2);
		return ;
	}
	tmp = gen.env;
	if (!tmp)
		return ;
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