#include "../includes/minishell.h"

void	cd_home(t_gen *gen)
{
    char *home;
    printf("ef");
    home =  find_value("HOME", gen->envp);
	if (chdir(home) == -1)
	{
		printf("problem in chdir\n");
		gen->exit_status = 1;
	}
}

int	ft_cd(t_gen *gen, char *path)
{
    printf("greg");
	if (!path || (path[0] == '~' && !path[1])) 
		cd_home(gen);
	else if (chdir(path) == -1)
	{
		printf("no such a directory");
	}
    
   //char *arr = ft_pwd(gen);
    //modify_env(gen->env, arr);
	return (gen->exit_status);
}


// char*     change_env2(t_gen *gen)
// {
//     t_list *tmp;
//     char *str = NULL;

//     tmp = env_create(gen->envp);
//     while(tmp != NULL)
//     {
//             if(ft_strncmp(tmp->content, "PWD=", 4) == 0)
//             {
//                 str = ft_substr(tmp->content, 5, (ft_strlen(tmp->content)) - 4);
//             }
//             tmp = tmp->next;
//     }
//     return (str);
// }

// void    modify_env(t_list *env, char *arr)
// {
//     t_list *tmp;
//     char *j = NULL;
    
    
//     tmp = env;
//     while(tmp != NULL)
//     {
//             if(ft_strncmp(tmp->content, "PWD=", 4) == 0)
//             {
//                 if(tmp->content)
//                 {
//                     free(tmp->content);
//                     tmp->content = NULL;
//                 }
//                 tmp->content = ft_strdup("hello");
//                 break ;
//             }
//             tmp = tmp->next;
//     }
//     return ;
// }





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


void	go_commands(t_gen *gen, char **line)
{
	if (!ft_strcmp("env", line[0]))
		ft_env(gen->env);
	if (!ft_strcmp("pwd", line[0]))
		printf("%s",ft_pwd());//it does not print the pwd
	// if (!ft_strcmp("pwd", line[0]))
	// 	printf("%s",ft_pwd(gen));//it does not print the pwd
	// if (!ft_strcmp("echo", line[0]))
	// 	ft_echo(gen, line);
	// if (!ft_strcmp("cd", line[0]))
	// 	ft_cd(gen, line[1]); //what if it has alot of spaces?
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

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}
