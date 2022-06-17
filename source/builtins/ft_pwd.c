#include "../includes/minishell.h"

//pwd should be returning char*
char* ft_pwd(void)
{
    char	pwd[PATH_MAX];
    char *str;

    str = NULL;
	str = getcwd(pwd, PATH_MAX);
	ft_putstr_fd(pwd, 1);
	ft_putchar_fd('\n', 1);
	gen->pwd = str;
	return (str);
}