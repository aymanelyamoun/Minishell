/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufisaou <oufisaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 19:19:26 by ael-yamo          #+#    #+#             */
/*   Updated: 2022/06/01 11:30:43 by oufisaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <readline/readline.h>
#include "../includes/minishell.h"


int	get_quote(char **str, char c)
{
    int	i;

    i = 1;
    while ((*str)[i] != '\0' && (*str)[i] != c)
        i++;
    *str = *str + i + 1;
	return (i + 1);
}

int	get_word(char **str)
{
    int	i;

    i = 0;
    while ((*str)[i] != '\0' \
	    && (*str)[i] != '\t' && (*str)[i] != '\v' \
	       && (*str)[i] != '\f' && (*str)[i] != ' ')
        i++;
    *str = *str + i;
	return (i);
}

char *get_char(char **str, char *c, int increment)
{
	*str = *str + increment;
	return (ft_strdup(c));
}

void	get_sympol_great(token_t **tokens, char **str)
{
	if (**str == '>' && *(*str + 1) != '\0' && *(*str + 1) == '>')
	{
		add_token_last(tokens, DGREAT, ft_strdup(">>"));
		*str = *str + 2;
	}
	else
	{
		add_token_last(tokens, GREAT, ft_strdup(">"));
		*str = *str + 1;
	}
}

void	get_sympol_less(token_t **tokens, char **str)
{
	if (**str == '<' && *(*str + 1) != '\0' && *(*str + 1) == '<')
	{
		add_token_last(tokens, DLESS, ft_strdup("<<"));
		*str = *str + 2;
	}
	else
	{
		add_token_last(tokens, LESS, ft_strdup("<"));
		*str = *str + 1;
	}
}

void    get_token(token_t **tokens, char **str)
{
	while (**str != '\0')
	{
		if (**str == '\"')
			add_token_last(tokens, DQUOTE, ft_substr(*str, 0, get_quote(str, '\"')));
		else if (**str == '\'')
			add_token_last(tokens, QUOTE, ft_substr(*str, 0, get_quote(str, '\'')));
		else if (**str == ' ') // IS SPACE!
			add_token_last(tokens, SPACE, get_char(str, " ", 1));
		else if (**str == '>')
			get_sympol_great(tokens, str);
		else if (**str == '<')
			get_sympol_less(tokens, str);
		else if (**str == '|')
			add_token_last(tokens, PIPE, get_char(str, "|", 1));
		else if (**str == '$')
			add_token_last(tokens, DOLLAR, get_char(str, "$", 1));
		else
			add_token_last(tokens, WORD, ft_substr(*str, 0, get_word(str, ' ')));
		//fix the word if it is folowed by a spectial char as < > | ...
	}
}

token_t *tokenize(char *line)
{
    // int i;
    token_t *tokens = NULL;
    token_t *tmp;

    // i = 0;
    get_token(&tokens, &line);
    tmp = tokens;
	// int j = 0;
    while (tokens != NULL)
    {
        tokens = tokens->next;
    }
    return (tmp);
}
//execv -> waitpid]wait -> 'status' -> macro value return pros $?*
