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
