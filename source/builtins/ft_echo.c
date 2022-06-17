#include "../includes/minishell.h"

 //where to put it ?

void	ft_echo(char **str) //hooooooooooooooooooow
{
	int index;

	index = 1;
	while(str[index] && !ft_strcmp("-n", str[index]))
		index++;
	if(index > 1 && str[index])
		ft_putstr_fd(str[index], 1);
	else if(index > 1 && !str[index])
		ft_putchar_fd('\n', 1);
	else if(ft_strcmp("$?", str[index]) == 0)
		ft_putnbr_fd(gen->exit_status, 1);
	else if(str[index])
	{
		ft_putstr_fd(str[index], 1);
		ft_putchar_fd('\n', 1);
	}
	gen->exit_status = 0;
}