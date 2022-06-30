#include "../includes/minishell.h"

t_list	*env_create(char **envp)
{
	t_list	*tmp;
	t_list	*head;
	char	*s;
	int		index;

	index = 1;
	tmp = NULL;
	head = NULL;
	if (!(envp) || !(*envp))
		return (NULL);
	if (!(envp[0]))
	{
		head = ft_lstnew(NULL);
		return (head);
	}
	s = ft_strdup(envp[0]);
	head = ft_lstnew(s);
	while (envp[index])
	{
		s = ft_strdup(envp[index]);
		tmp = ft_lstnew(s);
		ft_lstadd_back(&head, tmp);
		index++;
	}
	return (head);
}

char	**set_env(char **envp)
{
	int		index;
	char	**tmp;

	if (envp)
	{
		index = 0;
		while (envp[index])
			index++;
	}
	tmp = malloc(sizeof(char *) * (index + 1));
	if (!tmp)
		return (NULL);
	index = 0;
	while (envp[index])
	{
		tmp[index] = ft_strdup(envp[index]);
		index++;
	}
	tmp[index] = NULL;
	return (tmp);
}
