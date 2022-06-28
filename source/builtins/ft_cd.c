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

int find_plus(char *str)
{
	int index;
	int j;

	index = 0;
	j = 0;
	while(str[index])
	{
		if(str[index] == '+')
			j++;
		index++;
	}
	return (j);
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

//handle adding a new one if it sis 
//TODO: two problems: it writes character twice + it should add the variable if it is not here + the += should be handeled
//TODO: Norme should be handled
//TODO :Leaks

int append_case(t_list **env_list, char *str) //how to break this one
{
	int index = 0;
	int flag = 0;

	while (str[index])
	{
		if (str[index] == '+' && str[index + 1] == '=')
			break;
		index++;
	}
	char *var_name = ft_substr(str, 0, index);
	char *value = ft_substr(str, index + 2, ft_strlen(str) - (index + 2));
	t_list *head = *env_list;
	while(head)
	{
		index = 0;
		while (((char *)head->content)[index] && ((char *)head->content)[index] != '=')
			index++;
		// if (((char *)head->content)[index] != '=')
		// 	value = ft_strdup("");
		if (!ft_strncmp(ft_substr(((char *)head->content), 0, index), var_name, ft_strlen(var_name)))
		{
			// ft_putendl_fd((char *)head->content, 1);
			char *test = ft_strjoin(&((char *)head->content)[index], value);
			test = ft_strjoin("=", test);
			test = ft_strjoin(var_name, test);
			head->content = test;
			flag = 1;
			ft_putchar_fd('1', 1);
			break ;
		}
		head = head->next;
	}
	if(flag == 0)
	{
		ft_putstr_fd("2", 1);
		char *varr = ft_strjoin(var_name, "=");
		ft_lstadd_back(&gen.env, ft_lstnew(ft_strjoin(varr, value)));
		free(varr);
	}
	return (1);
}

// int append_it(t_list **env_list, char *str)
// {
// 	char *tmp_str;
// 	size_t index1;
// 	t_list *tmp;
// 	size_t index2;
// 	char **strr;

// 	tmp_str = ft_strdup(str);
// 	tmp = *env_list;
// 	while(tmp)
// 	{
// 		index1 = 0;
// 		index2 = 0;
// 		while(((char *)tmp->content)[index1] && ((char *)tmp->content)[index1] != '=')
// 			index1++;
// 		while(str[index2] && str[index2] != '=')
// 			index2++;
// 		if(!ft_strncmp(tmp->content, str, index1) && index1 == index2)
// 		{
// 			if(ft_strchr(str, '='))
// 			{
// 				strr = ft_split(tmp_str, '=');
// 				free(tmp->content);
// 				tmp->content = ft_strjoin(tmp->content, strr[1]);
// 			}
// 			return (1);
// 		}
// 		tmp = tmp->next;
// 	}
// 	free(tmp_str);
// 	return (0);
// }
