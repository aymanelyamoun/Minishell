#include "../includes/minishell.h"

int ft_pwd(void)
{
    char	pwd[PATH_MAX];

	getcwd(pwd, PATH_MAX);
	ft_putstr_fd(pwd, 1);
	ft_putchar_fd('\n', 1);
	return (0);
}