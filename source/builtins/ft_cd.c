#include "../includes/minishell.h"

int	modify_env(char *pwd)
{
	if (!ft_add_list(&gen.env, pwd))
		ft_lstadd_back(&gen.env, ft_lstnew(pwd));
	return (1);
}

int	small(char **p)
{
	*p = find_value("HOME", gen.env);
	if (!*p)
		ft_putstr_fd("Home not set\n", 2);
	if (chdir(*p) == -1)
	{
		ft_putstr_fd("Problem in chdir.\n", 2);
		gen.exit_status = 1;
		return (1);
	}
	return (0);
}

int	small2(char **p)
{
	*p = find_value("OLDPWD", gen.env);
	if (!*p)
		ft_putstr_fd("OLDPWD not set\n", 2);
	if (chdir(*p) == -1)
	{
		ft_putstr_fd("Problem in chdir.\n", 2);
		gen.exit_status = 1;
		return (1);
	}
	ft_putendl_fd(*p, 2);
	return (0);
}

int	ft_cd(char **path)
{
	char	*pwd;
	char	*p;

	if (!ft_strncmp(path[0], "CD", 2))
		return (0);
	if (!path[1] || !ft_strncmp(path[1], "--", 2) || \
	(!ft_strncmp(path[1], "~", 2) && !path[2]))
	{
		if (small(&p))
			return (1);
	}
	else if (!strncmp(path[1], "-", 1))
	{
		if (small2(&p))
			return (1);
	}
	else if (ft_strlen2(path) == 2)
		p = ft_strdup(path[1]);
	change_env(p);
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
int	change_env(char *p)
{
	char	*pwd;

	pwd = join_str("OLDPWD=", gen.pwd);
	if (chdir(p) != -1)
	{
		if (small3(&pwd))
			return (1);
	}
	else if (chdir(p) == -1)
		perror("cd");
	gen.pwd = getcwd(NULL, 0);
	gen.exit_status = 0;
	free(pwd);
	free(p);
	return (0);
}

int	suite6(char *str1, char *str)
{
	size_t index1;
	size_t index2;

	index1 = 0;
	index2 = 0;
	while (((char *)str1)[index1] && ((char *)str1)[index1] != '=')
		index1++;
	while (str[index2] && str[index2] != '=')
		index2++;
	if (!ft_strncmp(str1, str, index1) && index1 == index2)
	{
		if (ft_strchr(str, '='))
		{
			free(str1);
			str1 = ft_strdup(str);
		}
		return (1);
	}
	return (0);
}

int	ft_add_list(t_list **env_list, char *str)
{
	t_list	*tmp;

	tmp = *env_list;
	while (tmp)
	{
		suite6(tmp->content, str);
		tmp = tmp->next;
	}
	free(tmp);
	gen.exit_status = 0;
	return (0);
}
