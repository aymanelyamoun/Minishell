#include "../includes/minishell.h"

//TODO: FIX THE RETURN STATUS /VALUES
//TODO : FREE THE UNUSED ALLOCATIONS

int	ft_strlen2(char **str)
{
	int	index;

	index = 0;
	if (str)
		while (str[index])
			index++;
	return (index);
}             

int    modify_env(char *pwd)
{
	if(!ft_add_list(&gen->env, pwd))
        ft_lstadd_back(&gen->env, ft_lstnew(pwd));
	return (1);
}

int	ft_cd(char **path)
{
	char	*pwd;
	char	*p;

	if (!path[1] || !strncmp(path[1], "--", 2) || (!strncmp(path[1], "~", 2)&& !path[2]))
	{
		p =  find_value("HOME", gen->env);
		if(chdir(p) == -1)
		{
			ft_putstr_fd("Minishell : HOME not set.\n", 2);
			gen->exit_status = 1;
			return (1);
		}
	}
	else if(!strncmp(path[1], "-", 1))
	{
		p = find_value("OLDPWD", gen->env);
		if(chdir(p) == -1)
		{
			ft_putstr_fd("Minishell: OLDPWD not set.\n", 2);
			gen->exit_status = 1;
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

	pwd = join_str("OLDPWD=", gen->pwd);
	if(!chdir(p))
	{
		modify_env(pwd);
		free(pwd);
		pwd = join_str("PWD=", getcwd(NULL, 0));
		modify_env(pwd);
	}
	else
		perror("cd");
	free(p);
	gen->pwd = getcwd(NULL, 0);
	free(pwd);
	return (0);
}

//TODO : STRJOIN AND JOIN STR

char *join_str(char const *s1, char const *s2)
{
	int index;
	int len;
	char *s;

	if(!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1);
	s = (char *)malloc(sizeof(char) * (len + ft_strlen(s2) + 1));
	if(!s)
		return (NULL);
	index = 0;
	while(s1 && s1[index])
	{
		s[index] = s1[index];
		index++;
	}
	while(s2 && s2[index - len])
	{
		s[index] = s2[index - len];
		index++;
	}
	s[index] = '\0';
	return (s);
}
// <<<<<<< aymane_
// =======


// int ft_add_list(t_list **env_list, char *str)
// {
// 	t_list *tmp;
// 	size_t index1;
// 	size_t index2;

// 	if(!*env_list)
// 		return (0);
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
// 				free(tmp->content);
// 				tmp->content = ft_strdup(str);
// 			}
// 			return (1);
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }
// >>>>>>> main
