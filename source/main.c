
#include "../includes/minishell.h"

char **convert_to_array(t_list **env)
{
	int     index;
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
