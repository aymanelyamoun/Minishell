#include "../includes/minishell.h"

void	ft_pwd(void)
{

    char	pwd[PATH_MAX];
    char *str;

    str = NULL;
	str = getcwd(pwd, PATH_MAX); //copy pwd to ped array of size path_max
	ft_putstr_fd(str, 1);
	ft_putchar_fd('\n', 1);
	gen->pwd = str; //free str without error
	gen->exit_status = 0;
}
