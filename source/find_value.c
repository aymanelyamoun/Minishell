#include "../includes/minishell.h"

char *find_value(char *str, t_list *env_l)
{
	char *tmp;

	if (strcmp(str, "?") == 0)
		return (ft_itoa(gen.exit_status));
	while (env_l != NULL)
	{
		tmp = ft_strjoin(str, "=");
		if (ft_strncmp(tmp, env_l->content, ft_strlen(tmp)) == 0)
		{
			free(tmp);
			return (ft_strdup(&(env_l->content[ft_strlen(str) + 1])));
		}
		free(tmp);
		env_l = env_l->next;
	}
	return (ft_strdup(""));
}