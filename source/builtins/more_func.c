#include "../includes/minishell.h"

int	small(char **p)
{
	*p = find_value("HOME", gen.env);
	if (chdir(*p) == -1)
	{
		ft_putstr_fd("Home not set.\n", 2);
		gen.exit_status = 1;
		return (1);
	}
	return (0);
}

int	small2(char **p)
{
	*p = find_value("OLDPWD", gen.env);
	if (chdir(*p) == -1)
	{
		ft_putstr_fd("OLDPWD not set.\n", 2);
		gen.exit_status = 1;
		return (1);
	}
	ft_putendl_fd(*p, 2);
	return (0);
}

int	small3(char **pwd)
{
	char	*cwd;

	modify_env(*pwd);
	free(*pwd);
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("minishell: cd: error retrieving current directory: "
			"getcwd: cannot access parent directories");
		gen.exit_status = 1;
		return (1);
	}
	*pwd = join_str("PWD=", cwd);
	free(cwd);
	modify_env(*pwd);
	return (0);
}

int	s1(char *str)
{
	int	index1;

	index1 = 0;
	while (str[index1] && str[index1] != '=')
			index1++;
	return (index1);
}
