#include "../includes/minishell.h"

token_t *error_free(char *str, token_t *tokens)
{
    ft_putstr_fd("syntax error near ", 2);
    ft_putstr_fd("parse error near ", 2);
    ft_putstr_fd("\'", 2);
    ft_putstr_fd(str, 2);
    ft_putstr_fd("\'", 2);
	free_all(tokens);
	return (NULL);
}


void	free_all(token_t *tokens)
{
	token_t	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->data);
		tmp->data = NULL;
		free(tmp);
		tmp = NULL;
	}
}