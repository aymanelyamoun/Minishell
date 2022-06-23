#include "../includes/minishell.h"
#include "../includes/libft/libft.h"

char *find_value(char *str, t_list *env_l)
{
	int i;
	char *tmp;

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

char *rm_quotes(char *str, char c)
{
	int i;
	char *new;

	if (str[0] == c)
	{
		str[ft_strlen(str) - 1] = '\0';
		new = ft_strdup(&str[1]);
		free(str);
	}
	else
		new = str;
	return (new);
}

char *join_mix(token_t *token1, token_t *token2)
{
	char	*tmp;

	if (token1->data[0] == '\"' || token1->data[0] == '\'')
	{
		token1->data = rm_quotes(token1->data, token1->data[0]);
	}
	if (token2->data[0] == '\"' || token2->data[0] == '\'')
	{
		token2->data = rm_quotes(token2->data, token2->data[0]);
	}
	tmp = ft_strjoin(token1->data, token2->data);
	free(token1->data);
	return (tmp);
}

void join_word(token_t **tokens)
{
	token_t *tmp;
	// char	*to_free;

	tmp = *tokens;
	while (tmp != NULL)
	{
		if (tmp->type == WORD || tmp->type == DQUOTE || tmp->type == QUOTE)
		{
			while (tmp->next != NULL &&
				   (tmp->next->type == WORD || tmp->next->type == DQUOTE || tmp->next->type == QUOTE))
			{
				tmp->data = join_mix(tmp, tmp->next);
				tmp->type = WORD;
				rm_token(&(tmp->next));
			}
		}
		tmp = tmp->next;
	}
}

void	rm_quotes_tokens(token_t **tokens)
{
	token_t	*tmp;

	tmp = *tokens;
	while (tmp != NULL)
	{
		if (tmp->type == QUOTE || tmp->type == DQUOTE)
		{
			tmp->data = rm_quotes(tmp->data, tmp->data[0]);
			tmp->type = WORD;
		}
		tmp = tmp->next;
	}
}

void rm_token(token_t **tokens)
{
	token_t *token;

	token = *tokens;
	if (token->prev == NULL && token->next == NULL)
	{
		*tokens = NULL;
	}
	else if (token->prev == NULL)
	{
		*tokens = token->next;
		(*tokens)->prev = NULL;
	}
	else if (token->next == NULL)
	{
		(*tokens)->prev->next = NULL;
	}
	else
	{
		(*tokens)->next->prev = token->prev;
		(*tokens)->prev->next = token->next;
	}
	free(token->data);
	free(token);
}

void rm_spaces(token_t **tokens)
{
	token_t *tmp;
	int i = 0;

	while ((*tokens) != NULL && (*tokens)->type == SPAACE)
	{
		rm_token(tokens);
		i++;
	}
	tmp = *tokens;
	while (tmp != NULL)
	{
		if (tmp->type == SPAACE)
		{
			rm_token(&tmp);
			i++;
		}
		tmp = tmp->next;
	}
}

void change_data(token_t **tokens, char *data)
{
	if (ft_strcmp(data, "") == 0)
		(*tokens)->old_data = ft_strjoin("$", (*tokens)->next->data);
	free((*tokens)->data);
	(*tokens)->data = data;
	(*tokens)->type = WORD;
}

char	*get_var_str(char *str, int *i)
{
	*i = 0;
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		(*i)++;
	return (ft_substr(str, 0, *i));
}

void play_with_tokens(token_t **tokens, char *str, t_list *env)
{
	char	*env_var;
	char	*second_part;
	char	*new_str;
	int		i;

	new_str = get_var_str(str, &i);
	second_part = ft_substr(str, i, ft_strlen(str + i));
	env_var = find_value(new_str, env);
	env_var = ft_strjoin(env_var, second_part);
	free(second_part);
	free(new_str);
	if ((*tokens)->next->type == WORD)
	{
		if (env_var != NULL)
		{
			change_data(tokens, env_var);
		}
	}
	else if ((*tokens)->next->type == DOLLAR)
	{
		free((*tokens)->data);
		(*tokens)->data = ft_strdup("$$");
		(*tokens)->type = WORD;
	}
	else if ((*tokens)->next->type == DQUOTE)
	{
		free((*tokens)->data);
		(*tokens)->data = ft_strdup((*tokens)->next->data);
		(*tokens)->type = DQUOTE;
	}
	free(str);
	rm_token(&((*tokens)->next));
}

void expander(token_t **tokens, t_list *env_l)
{
	token_t *tmp;
	// char    **env = NULL;

	tmp = *tokens;
	while (tmp != NULL)
	{
		if (tmp->type == DOLLAR)
		{
			if (tmp->next != NULL && tmp->next->type != SPAACE &&
				(tmp->next->type == WORD || tmp->next->type == DQUOTE || tmp->next->type == DOLLAR))
				play_with_tokens(&tmp, ft_strdup(tmp->next->data), env_l);
			if ((tmp->next != NULL && tmp->next->type == SPAACE) || (tmp->next == NULL))
				tmp->type = WORD;
		}
		tmp = tmp->next;
	}
}

char *join(char *final_quote, char *tmp)
{
	char *to_free;

	to_free = final_quote;
	final_quote = ft_strjoin(final_quote, tmp);
	free(tmp);
	free(to_free);
	return (final_quote);
}

int	get_dollars(char *str)
{
	int	j;
	int	count;

	j = 0;
	while (str[j] != '\0' && str[j] == '$')
			j++;
	if ((j % 2 != 0) && str[j] != '\0' && j != 1)
		return (j - 1);
	else
		return (j);
}

char *get_var(char **str, char *final_quote, t_list *env)
{
	int i;
	char *env_var;
	char *to_free;

	i = 1;
	if ((*str)[0] == '$' && (*str)[1] != '\0' && ft_isalnum((*str)[1]))
	{
		while ((*str)[i] != '\0' && (*str)[i] != ' ' && (*str)[i] != '\t' 
		&& (*str)[i] != '\v' && (*str)[i] != '\f' && ft_isalnum((*str)[i]))
			i++;
		to_free = ft_substr(*str, 1, i - 1);
		env_var = find_value(to_free, env);
		free(to_free);
	}
	else
	{
		i = get_dollars(*str);
		env_var = ft_substr(*str, 0, i);
	}
	*str = *str + i;
	return (join(final_quote, env_var));
}

void expander_in_quotes_utils(token_t **token, t_list *env)
{
	char *str;
	int i;
	char *final_quote;
	char *tmp;

	str = (*token)->data;
	i = 0;
	final_quote = ft_strdup("");
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			tmp = ft_substr(str, 0, i);
			final_quote = join(final_quote, tmp);
			str = str + i;
			final_quote = get_var(&str, final_quote, env);
			i = -1;
		}
		i++;
	}
	tmp = ft_substr(str, 0, i);
	final_quote = join(final_quote, tmp);
	(*token)->data = final_quote;
}

void expander_in_quotes(token_t **tokens, t_list *env)
{
	token_t *token;

	token = *tokens;
	while (token != NULL)
	{
		if (token->type == DQUOTE)
		{
			expander_in_quotes_utils(&token, env);
		}
		token = token->next;
	}
}

int count_tokens(token_t *tokens)
{
	int count;

	count = 0;
	while (tokens)
	{
		tokens = tokens->next;
		count++;
	}
	return (count);
}

char **get_cmds(token_t *tokens)
{
	char	**cmds;
	int		i;

	i = 0;
	cmds = malloc(sizeof(char *) * (count_tokens(tokens) + 1));
	if (cmds == NULL)
		return (NULL);
	while (tokens)
	{
		cmds[i] = ft_strdup(tokens->data);
		tokens = tokens->next;
		i++;
	}
	cmds[i] = NULL;
	return (cmds);
}

void	clear_tokens(token_t **tokens)
{
	if (*tokens == NULL)
		return ;
	if ((*tokens)->next == NULL)
		rm_token(tokens);
	else
		rm_token(&((*tokens)->next));
	clear_tokens(tokens);
}

void creat_cmd_args(t_cmd **cmds, int pipe)
{
	int i;

	i = 0;
	while (i <= pipe)
	{
		(*cmds)[i].cmd_args = get_cmds((*cmds)[i].tokens_cmd);
		clear_tokens(&((*cmds)[i].tokens_cmd));
		i++;
	}
}

t_cmd *cmds_and_redirections(token_t **tokens, t_list *env_l, int *pipes)
{
	t_cmd	*cmds;
	int		status;

	*pipes = count_pipes(*tokens);
	cmds = creat_cmds(tokens);
	check_file_direcitons(&cmds, *pipes);
	rm_redirecitons(&cmds, *pipes);
	creat_cmd_args(&cmds, *pipes);
	
	return (cmds);
}

void	get_path_and_execute(token_t **toknes, t_list *env_l)
{
	t_cmd	*cmds;
	int		pipes_num;

	cmds = cmds_and_redirections(toknes, env_l, &pipes_num);
	if (get_cmds_path(&cmds, pipes_num, env_l) == 0)
	{	
		execution(cmds, pipes_num);
	}
}

int main(int argc, char **argv, char **envp)
{
	t_list *env_l;
	char *line;
	token_t *tokens;
	token_t *tok;
	t_cmd *cmds;

	int pipes;
	int i = 0;
	int j = 0;
	int	status;
	
    gen.envp = envp;
	gen.herdoc_num = 0;
	if(argc != 1)
	    return (1);
	env_l = env_create(envp);
	while (1)
	{
		line = readline("minishell> ");
		if (line != NULL)
		{
			add_history(line);
			tokens = tokenize(line);
			if (syntax_err(tokens))
			{
				expander(&tokens, env_l);
				expander_in_quotes(&tokens, env_l);
				join_word(&tokens);
				rm_spaces(&tokens);
				rm_quotes_tokens(&tokens);
				get_path_and_execute(&tokens, env_l);
			}
	
			// i = 0;
			// // while (i <= pipes)
			// // {
			// 	tok = tokens;
			// 	// tok = cmds[i].tokens_cmd;
				// printf("from main %d : ---infile: %d --- outfile: %d\n", i, cmds[i].infile, cmds[i].outfile);
			// 	while (tok != NULL)
			// 	{
			// 		printf(" -- %d ---> %s \n", tok->type, tok->data);
			// 		tok = tok->next;
			// 	}
			// 	// j = 0;
			// 	// while (cmds[i].cmd_args[j])
			// 	// {
			// 	// 	printf("arg %d : %s\n", j+1, cmds[i].cmd_args[j]);
			// 	// 	j++;
			// 	// }
// 			// 	i++;
// 			// // // }
		}
		else
		{
			printf("\ni got a NULL\n");
			exit(0); // last status
		}
	}
	return (0);
}

// // t_cmd   *parsing(token_t *kokens)
// // {

// // }
