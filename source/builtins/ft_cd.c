#include "../includes/minishell.h"

int    modify_env(char *pwd)
{
	if(!ft_add_list(&gen.env, pwd))
        ft_lstadd_back(&gen.env, ft_lstnew(pwd));
	return (1);
}

int	ft_cd(char **path)
{
	char	*pwd;
	char	*p;

	if (!path[1] || !strncmp(path[1], "--", 2) || (!strncmp(path[1], "~", 2) && !path[2]))
	{
		p =  find_value("HOME", gen.env);
		if(!p)
			ft_putstr_fd("Home not set\n", 2);
		if(chdir(p) == -1)
		{
			ft_putstr_fd("Problem in chdir.\n", 2);
			gen.exit_status = 1;
			return (1);
		}
	}
	else if(!strncmp(path[1], "-", 1))
	{
		p =  find_value("OLDPWD", gen.env);
		if(!p)
			ft_putstr_fd("OLDPWD not set\n", 2);
		if(chdir(p) == -1)
		{
			ft_putstr_fd("Problem in chdir.\n", 2);
			gen.exit_status = 1;
			return (1);
		}
	}
	else if(ft_strlen2(path) == 2)
		p = ft_strdup(path[1]);
	change_env(p);
	return (0);
}

int change_env(char *p)
{
	char *pwd;

	// ft_putstr_fd(gen.pwd, 2);
	pwd = join_str("OLDPWD=", gen.pwd);
	if(chdir(p) != -1)
	{
		modify_env(pwd);
		free(pwd);
		if (!getcwd(NULL, 0))
		{
			perror("minishell: cd: error retrieving current directory: "
				"getcwd: cannot access parent directories");
			return (1);
		}
		pwd = join_str("PWD=", getcwd(NULL, 0));
		modify_env(pwd);
	}
	else if(chdir(p) == -1)
		perror("cd");
	free(p);
	gen.pwd = getcwd(NULL, 0);
	return (0);
}

int ft_add_list(t_list **env_list, char *str)
{
	t_list *tmp;
	size_t index1;
	size_t index2;
	char *tmp_str;

	tmp = *env_list;
	tmp_str = ft_strdup(str);
	while(tmp)
	{
		index1 = 0;
		index2 = 0;
		while(((char *)tmp->content)[index1] && ((char *)tmp->content)[index1] != '=')
			index1++;
		while(str[index2] && str[index2] != '=')
			index2++;
		if(!ft_strncmp(tmp->content, str, index1) && index1 == index2)
		{
			if(ft_strchr(str, '='))
			{
				free(tmp->content);
				tmp->content = tmp_str;
			}
			return (1);
		}
		tmp = tmp->next;
	}
	free(tmp_str); //free everything
	return (0);
}


