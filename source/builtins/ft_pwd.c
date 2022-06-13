// #include "../includes/minishell.h"

// //pwd should be returning char*
// char* ft_pwd(void)
// {
//     char	pwd[PATH_MAX];

// 	getcwd(pwd, PATH_MAX);
// 	ft_putstr_fd(pwd, 1);
// 	ft_putchar_fd('\n', 1);
// 	return (pwd);
// }



// // char *ft_pwd(t_gen *gen)
// // {
// //     char	*pwd;

// // 	pwd = NULL;
// // 	pwd = getcwd(pwd, PATH_MAX);
// // 	if(!pwd)
// // 	{
// // 		printf("problem in pwd\n");
// // 		//track_status
// // 	}
// // 	return (change_env(gen, pwd));
// // }


// // char *change_env(t_gen *gen, char *new)
// // {
// // 	t_list *tmp;
// // 	tmp = env_create(gen->envp);
// // 	while(tmp)
// // 	{
// // 		if(strcmp(tmp->content, "PWD") == 0)
// // 			{
// // 				free(tmp->content);
// // 				tmp->content = ft_strdup(new);
// // 				free(new);
// // 				break ;
// // 			}
// // 			tmp = tmp->next;
// // 	}
// // 	return (new);
// // }