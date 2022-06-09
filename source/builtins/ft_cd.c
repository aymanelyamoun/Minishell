#include "../includes/minishell.h"

void    ft_cd(t_gen *gen, char *path)
{
    char *this_path;
    char *oldpwd;

    oldpwd = find_value("OLDPWD", gen->envp);
    gen->exit_status = 0;
    if(!ft_strncmp(path, "-", 1))
    {
        this_path = ft_strdup(oldpwd);
        if(!this_path)
        {
            printf("no old pwd");
            return ;
        }
        oldpwd_path(gen, this_path);
    }
    // else if((!this_path) || !ft_strncmp(path, "~", 1) || !ft_strncmp(path, "--", 2))
    // {
    //     //home_path
    // }
    // else
    // {
    //     //enter the path
    // }
    free(this_path);
}

void    oldpwd_path(t_gen *gen, char *this_path)
{
    printf("%s\n", this_path);
    go_path(gen, this_path);
}


void    go_path(t_gen *gen, char *this_path)
{
    char *path;
    char buffer[PATH_MAX];

    path = getcwd(buffer, PATH_MAX);
    


}