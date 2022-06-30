#include "../includes/minishell.h"

int	modify_env(char *pwd)
{
	if (!ft_add_list(&gen.env, pwd))
		ft_lstadd_back(&gen.env, ft_lstnew(pwd));
	return (1);
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
	free(p);
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
	if (gen.pwd != NULL)
		free(gen.pwd);
	gen.pwd = getcwd(NULL, 0);
	gen.exit_status = 0;
	free(pwd);
	return (0);
}

int	ft_add_list(t_list **env_list, char *str)
{
	t_list	*tmp;
	size_t	index2;

	tmp = *env_list;
	while (tmp)
	{
		index2 = s1(str);
		if (!ft_strncmp(tmp->content, str, index2))
		{
			if (ft_strchr(str, '='))
			{
				free(tmp->content);
				tmp->content = ft_strdup(str);
			}
			return (1);
		}
		tmp = tmp->next;
	}
	free(tmp);
	gen.exit_status = 0;
	return (0);
}
