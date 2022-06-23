#include "../includes/minishell.h"

int	ft_strlen2(char **str)
{
	int	index;

	index = 0;
	if (str)
		while (str[index])
			index++;
	return (index);
}

char *join_str(char const *s1, char const *s2)
{
	int index;
	int len;
	char *s;

	if(!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1);
	s = (char *)malloc(sizeof(char) * (len + ft_strlen(s2) + 1));
	if(!s)
		return (NULL);
	index = 0;
	while(s1 && s1[index])
	{
		s[index] = s1[index];
		index++;
	}
	while(s2 && s2[index - len])
	{
		s[index] = s2[index - len];
		index++;
	}
	s[index] = '\0';
	return (s);
    free(s);
}

void	free_split(char **array)
{
	int	index;

	index = 0;
	while (array[index])
	{
		free(array[index]);
		index++;
	}
	free(array);
}

void  print_err_exp(char *next)
{
    ft_putstr_fd("Minishell: export: `", 2);
	ft_putstr_fd(next, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int len_list(t_list **list)
{
    t_list *tmp;
    int index;

    index = 0;
    tmp = *list;
    while (tmp)
    {
        tmp = tmp->next;
        index++;
    }
    return (index);
}
