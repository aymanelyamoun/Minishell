#include "../includes/minishell.h"

void	ft_pwd(void)
{
    char	pwd[PATH_MAX];

    getcwd(pwd, PATH_MAX); //copy pwd to ped array of size path_max
	ft_putstr_fd(pwd, 1);
	ft_putchar_fd('\n', 1);
	gen.pwd = ft_strdup(pwd);
	gen.exit_status = 0;
}
