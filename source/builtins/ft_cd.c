#include "../includes/minishell.h"

static void	cd_home(t_gen *gen)
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
				break ;
			}
			tmp = tmp->next;
	}
}















// static int	change(char *path, int home)
// {
// 	char	*pwd;

// 	pwd = getcwd(NULL, 0);
// 	if (!chdir(path))
// 	{
// 		if (pwd)
// 		{
// 			set_env("OLDPWD", pwd);
// 			free(pwd);
// 		}
// 		if ((pwd = getcwd(NULL, 0)))
// 		{
// 			set_env("PWD", pwd);
// 			free(pwd);
// 		}
// 		if (home)
// 			free(path);
// 		return (1);
// 	}
// 	free(pwd);
// 	return (0);
// }


// int			set_env(char *env, char *new_env)
// {
// 	char	*tmp;
// 	ssize_t	i;
// 	size_t	len;

// 	if (!env || !new_env)
// 		return (0);
// 	len = ft_strlen(env);
// 	i = -1;
// 	if ((i = find_env(env)) != -1)
// 		return (modify(new_env, len, i));
// 	else
// 	{
// 		len = get_envs_count() + 1;
// 		g_envs = realloc_envs(len);
// 		tmp = ft_strjoin(env, "=");
// 		g_envs[len - 1] = ft_strjoin(tmp, new_env);
// 		free(tmp);
// 		return (1);
// 	}
// 	return (0);
// }

// ssize_t		find_env(char *env)
// {
// 	char	*sub;
// 	ssize_t i;
// 	ssize_t index;

// 	if (!env)
// 		return (-1);
// 	i = 0;
// 	sub = NULL;
// 	while (g_envs[i])
// 	{
// 		if ((index = ft_get_char_by_index(g_envs[i], '=')) == -1)
// 			index = ft_strlen(g_envs[i]);
// 		if ((sub = ft_substr(g_envs[i], 0, index)))
// 		{
// 			if (ft_strequ(sub, env))
// 			{
// 				free(sub);
// 				return (i);
// 			}
// 			free(sub);
// 		}
// 		i++;
// 	}
// 	return (-1);
// }