#include "../includes/minishell.h"

// TODO: -nnnnn-n fix

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
		while(str[index][j] && (str[index][j] == 'n' || (str[index][j] == ' ')))
				j++;
		index++;
		flag = 1;
	}
	while(str[index])
	{
		if(ft_strcmp("$?", str[index]) != 0)
			ft_putstr_fd(str[index], 1);
		else if(ft_strchr1(str[index], ' ') == 1)
			ft_putchar_fd(' ', 1);
		else if(ft_strcmp("$?", str[index]) == 0)
			ft_putnbr_fd(gen->exit_status, 1);
		if (str[index + 1])
			ft_putchar_fd(' ', 1);
		index++;
	}
	if(flag == 0)
		ft_putchar_fd('\n', 1);
	gen->exit_status = 0;
}


// void	ft_echo(char **str)
// {
// 	int index;
// 	int j;
// 	int flag;

// 	index = 1;
// 	flag = 0;
// 	j = 0;

// 	while(str[index] && !ft_strncmp("-n", str[index]))
// 	{
// 		index++;
// 		flag = 1;
// 	}



// }

int ft_strchr1(const char *str, int n)
{
	int	l_str;

	l_str = ft_strlen(str);
	while (l_str >= 0)
	{
		if (*str == (char)n)
			return (1);
		str++;
		l_str--;
	}
	return 0;
}
