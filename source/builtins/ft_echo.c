#include "../includes/minishell.h"

void	ft_echo(char **str) 
{
	int index;

	index = 1;
	while(str[index] && !ft_strcmp("-n", str[index]))
		index++;
	if(index > 1 && str[index])
	{
		ft_putstr_fd(str[index], 1);
	}
	else if(index > 1 && !str[index])
	{
		ft_putchar_fd('\n', 1);
	}
	while(str[index])
	{
		if(ft_strcmp("$?", str[index]))
		{
			ft_putstr_fd(str[index], 1);
			ft_putchar_fd(' ', 1);
		}
		else
		{
			ft_putnbr_fd(gen->exit_status, 1);
			ft_putchar_fd(' ', 1);
		}
		index++;
	}
	ft_putchar_fd('\n', 1);
	gen->exit_status = 0;
}