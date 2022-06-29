#include "../includes/minishell.h"

void suite3(char *str)
{
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(str, 1);
	ft_putchar_fd('\n', 1);
}

void	suite4(char *str)
{
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd("=", 1);
}
void	suite5(char *str1, char *str2)
{
	if (str1)
		ft_putstr_fd("\"", 1);
	ft_putstr_fd(str2, 1);
	if (str1)
		ft_putstr_fd("\"", 1);
}

void	print_export(t_list *env)
{
	int		index;
	char	**split;

	index = 0;
	if (!env)
		return ;
	while (env && env->content)
	{
		if (!ft_strchr(((char *)env->content), '='))
			suite3((char *)env->content);
		else
		{
			split = ft_split(env->content, '=');
			suite4(split[0]);
			if (split[1])
				suite5(split[0], split[1]);
			else
				ft_putstr_fd("\"\"", 1);
			ft_putchar_fd('\n', 1);
		}
		env = env->next;
	}
	free_split(split);
}

int	ft_export(char **next)
{
	int index;

	if (!gen.env)
		return (0);
	if (ft_strlen2(next) == 1)
	{
		ft_sort(&gen);
		return (0);
	}
	index = 1;
	while (next[index])
	{
		if (check_arg(next[index]))
		{
			print_err_exp(next[index]);
		}
		else if (!ft_add_list(&gen.env, next[index]))
			ft_lstadd_back(&gen.env, ft_lstnew(ft_strdup(next[index])));
		index++;
	}
	free_split(next);
	return (0);
}
