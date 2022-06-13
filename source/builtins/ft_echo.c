#include "../includes/minishell.h"

 //where to put it ?

void	ft_echo(t_gen *gen, char **str) //hooooooooooooooooooow
{
    int index;
	int	    flag;
	
	index = 1;
	flag = 0;
	if (str[1] && ft_strncmp(str[1], "-n", 2) == 0)
	{
		flag = 1;
		index = 2;
	}
	while (str && str[index])
	{
        ft_putstr_fd(str[index], 1);
		index++;
	}
	if (str[1] && flag == 0)
		ft_putstr_fd("\n", 1);
	gen->exit_status = 0;
}