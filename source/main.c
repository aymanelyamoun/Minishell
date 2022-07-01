
#include "../includes/minishell.h"

char	**convert_to_array(t_list **env)
{
	int		index;
	int     size;
	char    **arr;
	t_list  *tmp;

	size = len_list(env);
	tmp = *env;
	arr = (char **)malloc(sizeof(char *) * (size + 1));
	index = 0;
	while (tmp->next)
	{
		arr[index] = tmp->content;
		tmp = tmp->next;
		index++;
	}
	arr[index] = NULL;
	return (arr);
}