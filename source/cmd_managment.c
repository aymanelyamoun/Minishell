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



int	commands(char **line)
{
    if (!ft_strcmp("echo", line[0]))
		return (YES);
	if (!ft_strcmp("export ", line[0]))
		return (YES);
	if (!ft_strcmp("pwd", line[0]) && ft_strlen(line[0]) == 3)
		return (YES);
	if (!ft_strcmp("unset ", line[0]))
        return (YES);
	if (!ft_strcmp("env", line[0]))
		return (YES);
	if (!ft_strcmp("exit", line[0]) && ft_strlen(line[0]) == 4)
		return (YES);
	if (!ft_strcmp("cd", line[0]))
		return (YES);
	return (NO);
}

void	go_commands(t_gen *gen, char **line)
{
	if (!ft_strcmp("env", line[0]))
		ft_env(gen->env);
	if (!ft_strcmp("pwd", line[0]))
		printf("%s",ft_pwd(gen));//it does not print the pwd
	if (!ft_strcmp("echo", line[0]))
		ft_echo(gen, line);
	// if (!ft_strcmp("cd", line[0]))
	// 	ft_cd(gen, line[1]); //what if it has alot of spaces?
	return ;
}

int	array_len(char **array)
{
	int	index;

	index = 0;
	while (array[index + 1])
		index++ ;
	return (index);
}

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}