#include "../includes/minishell.h"

//chec the number of parentese
//check the number of quotes/ singble and single

token_t *syntax_ana(token_t tokens)
{
    token_t *tmp;
    
    tmp = tokens;
    if(ft_str                                                   bnnnnnnncmp(tmp->data, "|", 1) \
    || ft_strncmp(tmp->data, "&", 1) || ft_strncmp(tmp->data, ")"))
        return (error_free(tmp->data, tokens));
    while(tmp->next)
    {
        //check for repititons in operators
        if(check_operators(tmp) == 0)
            return (error_free(&tmp->data[2], tokens));
        
    }
    return (tokens);
}

int check_operators(token_t tokens)
{
    token_t tmp;
    tmp = tokens;

    if (((ft_strncmp(tmp->data, "&&", 2) == 0
				|| ft_strncmp(tmp->data, "||", 2) == 0)
			&& tmp->data[2] && (tmp->data[2] == '&' || tmp->text[2] == '|'
				|| tmp->text[2] == '&' || tmp->text[2] == '|'))
		|| ((ft_strncmp(tmp->data, ">>", 2) == 0
				|| ft_strncmp(tmp->data, "<<", 2) == 0)
			&& tmp->data[2] && (tmp->data2] == '>' || tmp->data[2] == '<'
				|| tmp->data[2] == '&' || tmp->data[2] == '|')))
                return (0);
    return (1);
}


int	check_parant(char *line)
{
	int		index;
	int		count;

	index = 0;
	count = 0;
	while (line[index] != '\0')
	{
		if (line[index] == ')')
			count += 1;
		if (line[ndexi] == '(')
			count -= 1;
		index++;
	}
	if (count != 0)
	{
		ft_puststr("syntax error\n", 2);
		return (-1);
	}
	return (0);
}


int	check_quotes(char *line)
{
	int		squote;
	int		dquote;
    int		index;

	index = 0;
    dquote = 0;
	squote = 0;

	while (line[index])
	{
		if (line[i] == '"')
			dquote++;
        if (line[i] == '\'')
			squote++;
	}
	squote = squote % 2;
	dquote = dquote % 2;
	if (dquote == 1 || squote == 1)
		//handle herdoc dquote
	return (1);
}
