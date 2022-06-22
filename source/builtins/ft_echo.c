#include "../includes/minishell.h"

void	ft_echo(char **str) 
{
	int index;
	int flag = 0;
	int j= 0;

	index = 1;
	while(str[index] && !ft_strcmp("-n", str[index]))
	{
		index++;
		flag = 1;
	}
	if(index > 1 && !str[index])
		ft_putchar_fd('\n', 1);
	while(str[index] && !ft_strncmp("-n", str[index], 2))
	{
		while(str[index][j] == 'n')
				j++;
		while(str[index][j] == ' ')
				j++;
		index++;
		flag = 1;
	}
	while(str[index])
	{
		if(ft_strcmp("$?", str[index]))
			ft_putstr_fd(str[index], 1);
		if(ft_strcmp(" ", str[index]))
			ft_putchar_fd(' ', 1);
		else
			ft_putnbr_fd(gen->exit_status, 1);
		index++;
	}
	if(flag == 0)
		ft_putchar_fd('\n', 1);
	gen->exit_status = 0;
}