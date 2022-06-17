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
	if (!ft_strcmp("env", line[0]))
		ft_env();
	if (!ft_strcmp("pwd", line[0]))
		ft_pwd();//it does not print the pwd
	if (!ft_strcmp("echo", line[0]))
		ft_echo(line);
	if (!ft_strcmp("cd", line[0]))
		ft_cd(line[1]);
	// if (!ft_strcmp("exit", line[0]))
	// 	ft_exit();
	return ;
}

int	array_len(char **array)
{
	int	index;

	index = 0;
	while (array[index + 1])
		index++ ;
	return (index);
}
