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

	if(!strncmp(path[0], "CD", 2))
		return (0);
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
		p = find_value("OLDPWD", gen.env);
		if(!p)
			ft_putstr_fd("OLDPWD not set\n", 2);
		if(chdir(p) == -1)
		{
			ft_putstr_fd("Problem in chdir.\n", 2);
			gen.exit_status = 1;
			return (1);
		}
		ft_putendl_fd(p, 2);
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
	char **split;

	tmp = *env_list;
	tmp_str = ft_strdup(str);
	split = ft_split(str, '+');
	if(ft_strlen2(split) > 1)
	{
		append_case(&gen.env, str);
		return (1);
	}
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
	free_split(split);
	free(tmp_str); //free everything
	return (0);
}



void append_case(t_list **env_list, char *str)
{
	char **split;
	char *str3;
	char *part;
	char **split2; //put split 2 is split 1 by freeing
	char *str2;

	split2 = ft_split(str, '+');
	if(split2)
	{
		part = split2[0];
		split = ft_split(str, '=');
	}
	str2 = ft_strjoin("=", split[1]);
	str3 = ft_strjoin(part, str2);
	puts(str3);
	if(!append_it(&gen.env, str3))
		 ft_lstadd_back(&gen.env, ft_lstnew(str3));
	return ;
}

int append_it(t_list **env_list, char *str)
{
	char *tmp_str;
	size_t index1;
	t_list *tmp;
	size_t index2;
	char *strr;

	tmp_str = ft_strdup(str);
	tmp = *env_list;
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
				strr = tmp->content;
				free(tmp->content);
				tmp->content = ft_strjoin(strr, tmp_str);
			}
			return (1);
		}
		tmp = tmp->next;
	}
	free(tmp_str);
	return (0);
}