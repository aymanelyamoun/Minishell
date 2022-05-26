#include "../includes/minishell.h"

//chec the number of parentese
//check the number of quotes/ singble and single

// token_t *syntax_ana(token_t *tokens)
// {
//     token_t *tmp;
    
//     tmp = tokens;
//     if(ft_strcmp(tmp->data, "|", 1) 
//     || ft_strncmp(tmp->data, "&", 1) || ft_strncmp(tmp->data, ")"))
//         return (error_free(tmp->data, tokens));
//     // while(tmp->next)
//     // {
//     //     //check for repititons in operators
//     //     if(check_operators(tmp) == 0)
//     //         return (error_free(&tmp->data[2], tokens));
        
//     // }
// 	printf("all well");
//     return (tokens);
// }

// int check_operators(token_t *tokens)
// {
//     token_t tmp;
//     tmp = tokens;

//     if (((ft_strncmp(tmp->data, "&&", 2) == 0
// 				|| ft_strncmp(tmp->data, "||", 2) == 0)
// 			&& tmp->data[2] && (tmp->data[2] == '&' || tmp->text[2] == '|'
// 				|| tmp->text[2] == '&' || tmp->text[2] == '|'))
// 		|| ((ft_strncmp(tmp->data, ">>", 2) == 0
// 				|| ft_strncmp(tmp->data, "<<", 2) == 0)
// 			&& tmp->data[2] && (tmp->data[2] == '>' || tmp->data[2] == '<'
// 				|| tmp->data[2] == '&' || tmp->data[2] == '|')))
//                 return (0);
//     return (1);
// }


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
		if (line[index] == '(')
			count -= 1;
		index++;
	}
	if (count != 0)
	{
		ft_putstr_fd("bash:syntax error\n", 2);
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

	while (*(line + index))
	{
		if (*(line + index) == '"')
			dquote++;
		if (*(line + index) == '\'')
			squote++;
		index++;
	}
	if ((squote % 2) != 0 || (dquote % 2) != 0)
	{
		handle_herdoc(envi, squote, dquote);
	}	
	return (0);
}


//if you find a quote search the last