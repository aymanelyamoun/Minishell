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












