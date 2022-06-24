#include "../includes/minishell.h"

int	commands(char **line)
{
    if (!ft_strcmp("echo", line[0]))
		return (YES);
	if (!ft_strcmp("export", line[0]))
		return (YES);
	if (!ft_strcmp("pwd", line[0]) && ft_strlen(line[0]) == 3)
		return (YES);
	if (!ft_strcmp("unset", line[0]))
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
	// fprintf(stderr, "hi from go cmd\n");
	if (!ft_strncmp("env", line[0], 3))
		ft_env();
	if (!ft_strncmp("pwd", line[0],3))
		ft_pwd();
	if (!ft_strncmp("echo", line[0], 4))
		ft_echo(line);
	if(!ft_strncmp("export", line[0], 6))
		ft_export(line);
	if (!ft_strncmp("cd", line[0], 2))
	{
		// fprintf(stderr, "hi from go cmd cd\n");
		if(ft_strlen2(line) > 2)
			ft_putstr_fd("too much arguments\n", 2);
		else
			ft_cd(line);
	}
	if(!ft_strncmp("unset", line[0], 6))
		ft_unset(line);
	if(!ft_strncmp("exit", line[0], 4))
		ft_exit(line);
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