#include "../includes/minishell.h"

int	count_pipes(token_t *tokens)
{
	int	i;

	i = 0;
	while (tokens != NULL)
	{
		if (tokens->type == PIPE)
			i++;
		tokens = tokens->next;
	}
	return (i);
}

static t_cmd *creat_cmds_utils(token_t **tokens, t_cmd **cmds)
{
    token_t *tmp;
    token_t *new_head;
    int     i;

    i = 0;
	tmp = *tokens;
	new_head = tmp;
	while (tmp != NULL)
	{
		if (tmp->next != NULL && tmp->next->type == PIPE)
		{
			rm_token(&(tmp->next));
			(*cmds)[i].tokens_cmd = new_head;
			new_head = tmp->next;
			new_head->prev = NULL;
			tmp->next = NULL;
			tmp = new_head;
			i++;
		}
        else
		    tmp = tmp->next;
	}
    (*cmds)[i].tokens_cmd = new_head;
	return (*cmds);
}

t_cmd   *creat_cmds(token_t **tokens)
{
    int		pipes;
	token_t	*new_head;
	token_t *tmp;
	t_cmd	*cmds;
	int		i;

	i = 0;
	pipes = count_pipes(*tokens);
	cmds = malloc(sizeof(t_cmd) * (pipes + 1));
	if (pipes == 0)
	{
		cmds[i].tokens_cmd = *tokens;
		return (cmds);
	}
    return (creat_cmds_utils(tokens, &cmds));
}