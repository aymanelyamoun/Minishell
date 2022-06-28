#include "../includes/minishell.h"


// void	print_export(t_list *env)
// {
// 	int		index;
// 	char	**split;

// 	index = 0;
// 	if(!env)
// 		return ;
// 	while (env && env->content)
// 	{
// 		if (!ft_strchr(((char *)env->content), '='))
// 		{
// 			ft_putstr_fd("declare -x ", 1);
// 			ft_putstr_fd((char *)env->content, 1);
// 			ft_putchar_fd('\n', 1);
// 		}
// 		else
// 		{
// 			split = ft_split(env->content, '=');
// 			ft_putstr_fd("declare -x ", 1);
// 			ft_putstr_fd(split[0], 1);
// 			ft_putstr_fd("=", 1);
// 			if (split[1])
// 			{
// 				if(split[0])
// 					ft_putstr_fd("\"", 1);
// 				ft_putstr_fd(split[1], 1);
// 				if(split[0])
// 					ft_putstr_fd("\"", 1);
// 			}
// 			else
// 				ft_putstr_fd("\"\"", 1);
// 			ft_putchar_fd('\n', 1);
// 		}
// 		env = env->next;
// 	}
// 	free_split(split);
// }


//we will itterate on the env list
//if there is no = we just print declare and the var
//other wise we itterate until = and we print the string and =
//then we print " and the rest and again the ". 
//otherwise we only print ""


void	print_export(t_list *env)
{
	int index;

	index = 0;
	while(env && env->content)
	{
		if(!ft_strchr((char *)env->content), '=')
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd((char *)env->content, 1);
			ft_putchar_fd('\n', 1);
		}
		else
		{
			while(((char *)env->content)[index] && ((char *)env->content)[index] != '=')
			{
				ft_putstr_fd("declare -x ", 1);
				ft_putstr_fd((char *)env->content)[index], 1);
				ft_putstr_fd("=", 1);
			}
			if(((char *)env->content)[index] != '\0')
			{
				char *rest = ft_substr(((char *)env->content), index + 1, ft_strlen((char *)env->content) - (index + 1));
				ft_putstr_fd("\"", 1);
				ft_putstr_fd(rest, 1);
				if(str)
					ft_putstr_fd("\"", 1);
				else
					ft_putstr_fd("\"\"", 1);
				ft_putchar_fd('\n', 1);
			}
		}


	}
}
// void	print_export(t_list *env)
// {
// 	int index;
	
// 	index = 0;
// 	if(!env)
// 		return ;
// 	while(env && env->content)
// 	{
// 		// if (!ft_strchr(((char *)env->content), '='))
// 		// {
// 		// 	ft_putstr_fd("declare -x ", 1);
// 		// 	ft_putstr_fd((char *)env->content, 1);
// 		// 	ft_putchar_fd('\n', 1);
// 		// }
// 		// else
// 		// {
// 			while (((char *)env->content)[index] && ((char *)env->content)[index] != '=')
// 				index++;
// 			printf("%d", index);
// 			char *str = ft_substr(((char *)env->content), 0, index);
// 			printf("------>str:%s\n", str);
// 			char *rest = ft_substr(str, index + 1, ft_strlen(str) - (index + 1));
// 			printf("------>rest:%s\n", rest);
// 			// ft_putstr_fd("declare -x ", 1);
// 			// ft_putstr_fd(str, 1);
// 			// ft_putstr_fd("=", 1);
// 			// if (rest)
// 			// {
// 			// 	if(str)
// 			// 		ft_putstr_fd("\"", 1);
// 			// 	ft_putstr_fd(rest, 1);
// 			// 	if(str)
// 			// 		ft_putstr_fd("\"", 1);
// 			// }
// 			// else
// 			// 	ft_putstr_fd("\"\"", 1);
// 			// ft_putchar_fd('\n', 1);

// 		}
// 		env = env->next;
// 	}
// }



int	ft_export(char **next)
{
	int		index;

	if (!gen.env)
		return (0);
	if (ft_strlen2(next) == 1)
	{
		ft_sort(&gen);
		return (0);
	}
	index = 1;
	if (find_plus(next[index]) >= 1)
	{
		append_case(&gen.env, next[index]);
		return (0);
	}
	while (next[index])
	{
		if (check_arg(next[index]))
			print_err_exp(next[index]);
		else if (!ft_add_list(&gen.env, next[index]))
			ft_lstadd_back(&gen.env, ft_lstnew(ft_strdup(next[index])));
		index++;
	}
	return (0);
}

