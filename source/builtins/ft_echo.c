#include "../includes/minishell.h"

void	ft_echo(char **str) 
{
	int index;
	int flag;

	flag = 0;
	if(ft_strlen2(str) == 1 || (ft_strlen2(str) != 1 && !str[index + 1]))
	{
		ft_putchar_fd('\n', 1);
		return ;
	}
	index = 1;
	while (str[index] && set_flag(str[index]))
	{
		flag = 1;
		index++;
	}
	while(str[index])
	{
		ft_putstr_fd(str[index], 1);
		index++;
		if(str[index])
			ft_putchar_fd(' ', 1);
	}
	if (flag == 0)
		ft_putchar_fd('\n', 1);
	return ;
}


int set_flag(char *s)
{
	int index;
	int size;

	if (!s)
		return (0);
	index = 0;
	size = ft_strlen(s);
	if(s[index] == '-')
	{
		index++;
		while(s[index] == 'n')
			index++;
	}
	if(index == size && index != 1)
	{
		return (1);
	}
	return (0);
}
