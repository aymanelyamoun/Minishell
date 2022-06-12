#include "../includes/minishell.h"

void	cd_home(t_gen *gen)
{
    char *home;

    home =  find_value("HOME", gen->envp);
	if (chdir(home) == -1)
	{
		printf("problem in chdir\n");
		gen->exit_status = 1;
	}
}

int	ft_cd(t_gen *gen, char *path)
{
	if (!path || (path[0] == '~' && !path[1])) 
		cd_home(gen);
	else if (chdir(path) == -1)
	{
		printf("no such a directory");
	}
    change_env2(gen);
	return (gen->exit_status);
}


void change_env2(t_gen *gen)
{
	t_list *tmp;
	tmp = env_create(gen->envp);
	while(tmp)
	{
		if(strcmp(tmp->content, "OLDPWD")== 0)
			{
                if(tmp->content)
                {
                    free(tmp->content);
                    tmp->content = NULL;
                }
				tmp->content = ft_strdup(find_value("PWD", gen->envp));
				printf("%s\n", tmp->content);
				break ;
			}
			tmp = tmp->next;
	}
}














