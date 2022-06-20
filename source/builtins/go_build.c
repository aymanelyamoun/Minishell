#include "../includes/minishell.h"

int	commands(char **line)
{
    if (!ft_strcmp("echo", line[0]))
		return (YES);
	if (!ft_strcmp("export ", line[0]))
		return (YES);
	if (!ft_strcmp("pwd", line[0]) && ft_strlen(line[0]) == 3)
		return (YES);
	if (!ft_strcmp("unset ", line[0]))
        return (YES);
	if (!ft_strcmp("env", line[0]))
		return (YES);
	if (!ft_strcmp("exit", line[0]) && ft_strlen(line[0]) == 4)
		return (YES);
	if (!ft_strcmp("cd", line[0]))
		return (YES);
	return (NO);
}


void	go_commands(char **line)
{
	if (!ft_strncmp("env", line[0], 3))
		ft_env();
	if (!ft_strncmp("pwd", line[0], 3))
		ft_pwd();//it does not print the pwd
	if (!ft_strncmp("echo", line[0], 4))
		ft_echo(line);
	if (!ft_strncmp("cd", line[0], 2))
	{
		if(ft_strlen2(line) > 2)
			ft_putstr_fd("too much arguments\n", 2);
		else
			ft_cd(line);
	}
	// if (!ft_strcmp("exit", line[0]))
	// 	ft_exit();
	return ;
}

int	ft_strlen2(char **str)
{
	int	index;

	index = 0;
	if (str)
		while (str[index])
			index++;
	return (index);
}             
