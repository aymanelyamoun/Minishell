#include "../includes/minishell.h"

void	change_data(t_token **tokens, char *data)
{
	(*tokens)->old_data = ft_strjoin("$", (*tokens)->next->data);
	free((*tokens)->data);
	(*tokens)->data = data;
	(*tokens)->type = WORD;
}

void	play_with_tokens(t_token **tokens, char *str, t_list *env)
{
	char	*env_var;

	env_var = get_env_var(str, env);
	if ((*tokens)->next->type == WORD)
	{
		if (env_var != NULL)
			change_data(tokens, env_var);
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

void	expander(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp != NULL)
	{
		if (tmp->type == DOLLAR)
		{
			if (tmp->next != NULL && tmp->next->type != SPAACE && \
				(tmp->next->type == WORD || tmp->next->type == DQUOTE \
				|| tmp->next->type == DOLLAR))
				play_with_tokens(&tmp, ft_strdup(tmp->next->data), gen.env);
			else if ((tmp->next != NULL && tmp->next->type == SPAACE) \
			|| (tmp->next == NULL))
				tmp->type = WORD;
		}
		tmp = tmp->next;
	}
}

char	*get_var_utils(char **str, int *i, t_list *env)
{
	char	*env_var;
	char	*to_free;	

	while ((*str)[*i] != '\0' && (*str)[*i] != ' ' && (*str)[*i] != '\t' && \
	(*str)[*i] != '\v' && (*str)[*i] != '\f' && (ft_isalnum((*str)[*i]) \
	|| (*str)[*i] == '?' || (*str)[*i] == '_'))
	{
		if (*i == 1 && (ft_isdigit((*str)[*i]) || (*str)[*i] == '?'))
		{
			(*i)++;
			break ;
		}
		(*i)++;
	}
	to_free = ft_substr(*str, 1, *i - 1);
	env_var = find_value(to_free, env);
	free(to_free);
	return (env_var);
}

char *get_var(char **str, char *final_quote, t_list *env)
{
	int i;
	char *env_var;

	i = 1;
	if ((*str)[0] == '$' && (*str)[1] != '\0' 
	&& ((ft_isalnum((*str)[1]) || (*str)[1] == '?' || (*str)[1] == '_')))
	{
		env_var = get_var_utils(str, &i, env);
	}
	else
	{
		i = get_dollars(*str);
		env_var = ft_substr(*str, 0, i);
	}
	*str = *str + i;
	return (join(final_quote, env_var));
}

void	expander_in_quotes_utils(t_token **token, t_list *env)
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
	free((*token)->data);
	(*token)->data = final_quote;
}

void	expander_in_quotes(t_token **tokens)
{
	t_token	*token;

	token = *tokens;
	while (token != NULL)
	{
		if (token->type == DQUOTE)
		{
			expander_in_quotes_utils(&token, gen.env);
		}
		token = token->next;
	}
}

int	count_tokens(t_token *tokens)
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

char **get_cmds(t_token *tokens)
{
	char	**cmds;
	int		i;

	i = 0;
	cmds = (char **)malloc(sizeof(char *) * (count_tokens(tokens) + 1));
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

void	clear_tokens(t_token **tokens)
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

t_cmd *cmds_and_redirections(t_token **tokens, int *pipes)
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

void	get_path_and_execute(t_token **toknes)
{
	t_cmd	*cmds;
	int		pipes_num;

	cmds = cmds_and_redirections(toknes, &pipes_num);
	if (get_cmds_path(&cmds, pipes_num) == 0 && gen.skip_all == 0) 
		execution(cmds, pipes_num);
	free_cmds(cmds, pipes_num);
}

int main(int argc, char **argv, char **envp)
{
	char	*line;
	t_token *tokens;
	t_cmd	*cmds;
	char	p[PATH_MAX];

	getcwd(p, PATH_MAX);
	gen.pwd = ft_strdup(p);
	gen.env = env_create(envp);
	gen.envp = NULL;
	gen.exit_status = 0;
	gen.exec = 0;
	handle_signals();
	if (argc != 1)
		return (1);
	while (1)
	{
		line = readline("\033[0;36m\x1B[1mminishell> \033[0;37m");
		if (line != NULL)
		{
			add_history(line);
			tokens = tokenize(line);
			free(line);
			if (syntax_err(tokens))
			{
				expander(&tokens);
				expander_in_quotes(&tokens);
				join_word(&tokens);
				rm_spaces(&tokens);
				rm_quotes_tokens(&tokens);
				gen.exec = 0;
				gen.skip_all = 0;
				get_path_and_execute(&tokens);
			}
		}
		else
			ctrld();
	}
	return (0);
}
