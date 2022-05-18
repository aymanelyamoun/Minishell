/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-yamo <ael-yamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 19:19:26 by ael-yamo          #+#    #+#             */
/*   Updated: 2022/05/18 22:18:33 by ael-yamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include "../includes/minishell.h"
#include "../../libft/libft.h"

int	get_len_q(char *str, char q)
{
	int i;

	i = 0;
	while (str[i] && str[i] != q)
	{
		i++;
	}
	return (i);
}

int single_or_double(char *str, char sample)
{
    if (*str == sample && *(str + 1) == sample)
       return (2);
    return (1);
}

void    get_token(token_t *tokens, char *str)
{
    int tmp;

    if (*str == '\'')
	{
        add_token_last(tokens, QUOTE, ft_substr(str, 0, get_len_q(str, '\'')));
		str = str + get_len_q(str, '\'');
	}
    else if (*str == '\"')
	{
        add_token_last(tokens, DQUOTE, ft_substr(str, 0, get_len_q(str, '\"')));
		str = str + get_len_q(str, '\"');
	}
	else if (*str == '<')
    {
        tmp = single_or_double(str, '<');
        if (tmp == 1)
		    add_token_last(tokens, LESS, ft_substr(str, 0, tmp));
        else
		    add_token_last(tokens, DLESS, ft_substr(str, 0, tmp));
        str = str + tmp;
    }
	else if (*str == '>')
    {
        tmp = single_or_double(str, '<');
        if (tmp == 1)
		    add_token_last(tokens, GREAT, ft_substr(str, 0, single_or_double(str, '<')));
        else
		    add_token_last(tokens, DGREAT, ft_substr(str, 0, single_or_double(str, '<')));
        str = str + tmp;
    }
	else if (*str == '|')
    {
		add_token_last(tokens, PIPE, ft_strdup("|"));
        str++;   
    }
	else if (*str == '\\')
    {
		add_token_last(tokens, BACKSLASH, ft_strdup("\\"));
        str++;
    }
    else if (*str == '\n')
    {
		add_token_last(tokens, NEWLINE, ft_strdup("\n"));
        str++;   
    }
    else if (*str == ' ')
    {
		add_token_last(tokens, SPACE, ft_strdup(" "));
        str++;
    }
    else if (*str == '$')
    {
		add_token_last(tokens, SPACE, ft_strdup("$"));
        str++;
    }
    else
    {
        add_token_last(tokens, WORD, ft_substr(str, 0, get_len_q(str, ' ')));
        str += get_len_q(str, ' ');
    }
}

token_t *tokenize(char *line)
{
    int i;
    token_t *tokens;
    token_t *tmp;

    i = 0;
    while (*line)
    {
        get_token(tokens, line);
    }
    tmp = tokens;
    // while (tokens != NULL)
    // {
    //     printf("data: %s ... type: %d\n", tokens->data, tokens->type);
    //     tokens = tokens->next;
    // }
    return (tmp);
}

int main(void)
{
    char *line;
    token_t *tokens;

    while (1)
    {
        line = readline("ENTER PROMPT   ");
        if (line != NULL)
        {
            add_history(line);
            tokens = tokenize(line);
        }
    }
    return (0);
}