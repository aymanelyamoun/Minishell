#include "../includes/minishell.h"

void	cd_home(t_gen *gen)
{
    char *home;
    home =  find_value("HOME", gen->env);
	if (chdir(home) == -1)
	{
		printf("problem in chdir\n");
		gen->exit_status = 1;
	}
	return ;
}

int	ft_cd(char *path)
{
	char *pwd;

	if (!path || (path[0] == '~' && !path[1])) 
		cd_home(gen);
	gen->pwd = ft_pwd();
	pwd = ft_strjoin_free("OLDPWD=", gen->pwd);
	if (!chdir(path))
	{
		modify_env(pwd);
		free(pwd);
		pwd = ft_strjoin_free("PWD=", gen->pwd);
		modify_env(pwd);
	}
	else if (chdir(path) == -1)
	{
		perror("cd");
		gen->exit_status = 1;
	}
	free(path);
	gen->pwd = getcwd(NULL, 0);
	free(pwd);
	return(gen->exit_status);
}

int    modify_env(char *pwd)
{
	if(!ft_add_list(&gen->env, pwd))
        ft_lstadd_back(&gen->env, ft_lstnew(pwd));
	return (1);
}

char *ft_strjoin_free(char const *s1, char const *s2)
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


int ft_add_list(t_list **alst, char *str)
{
	t_list *tmp;
	size_t index1;
	size_t index2;

	tmp = *alst;
	index1 = 0;
	index2 = 0;
	while(tmp)
	{
		index1 = 0;
		index2 = 0;

		while(str[index2] && str[index2] != '=')
			index2++;
		while(((char *)tmp->content)[index1] \
		&& ((char *)tmp->content)[index2] != '=')
			index1++;
		if(!ft_strncmp(tmp->content, str, index1) && index1 == index2)
		{
			if(ft_strchr(str, '='))
			{
				free(tmp->content);
				tmp->content = ft_strdup(str);
			}
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

