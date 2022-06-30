/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufisaou <oufisaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 19:19:26 by ael-yamo          #+#    #+#             */
/*   Updated: 2022/06/29 20:07:24 by oufisaou         ###   ########.fr       */
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

int	get_word(char **str, int *here, int *here2)
{
    int	i;

    i = 0;
	if (*here)
	{
		while (((*str)[i] != '\0' && (*str)[i] != ' ' 
			&& (*str)[i] != '\t' && (*str)[i] != '\v' && (*str)[i] != '\f'
			&& (*str)[i] != '<' && (*str)[i] != '>' && (*str)[i] != '|'
		))
			i++;
		*here = 0;
		*here2 = 1;
	}
	else
    {
		while ((*str)[i] != '\0' && ((*str)[i] != ' ' 
		&& (*str)[i] != '\t' && (*str)[i] != '\v' && (*str)[i] != '\f'
		&& (*str)[i] != '<' && (*str)[i] != '>' && (*str)[i] != '\"' 
		&& (*str)[i] != '\'' && (*str)[i] != '|' && (*str)[i] != '$'
		))
 	       i++;
	}
    *str = *str + i;
	return (i);
}

char *get_char(char **str, char *c, int increment)
{
	*str = *str + increment;
	return (ft_strdup(c));
}

void	get_sympol_great(t_token **tokens, char **str)
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

void	get_sympol_less(t_token **tokens, char **str, int *here)
{
	if (**str == '<' && *(*str + 1) != '\0' && *(*str + 1) == '<')
	{
		add_token_last(tokens, DLESS, ft_strdup("<<"));
		*here = 1;
		*str = *str + 2;
	}
	else
	{
		add_token_last(tokens, LESS, ft_strdup("<"));
		*str = *str + 1;
	}
}

void	get_token_utils(t_token **tokens, char **str, int *here, int *here2)
{
	t_token *tmp;

	add_token_last(tokens, WORD, ft_substr(*str, 0, get_word(str, here, here2)));
	if (*here2 == 1)
	{
		tmp = *tokens;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->old_data = ft_strdup(tmp->data);
		*here2 = 0;
	}
}

void    get_token(t_token **tokens, char **str)
{
	int	here;
	int	here2;
	t_token *tmp;

	here = 0;
	here2 = 0;
	while (**str != '\0')
	{
		if (**str == '\"' && here == 0)
			add_token_last(tokens, DQUOTE, ft_substr(*str, 0, get_quote(str, '\"')));
		else if (**str == '\'' && here == 0)
			add_token_last(tokens, QUOTE, ft_substr(*str, 0, get_quote(str, '\'')));
		else if (**str == ' ' || **str == '\t' || **str == '\v' || **str == '\f') // IS SPAACE!
			add_token_last(tokens, SPAACE, get_char(str, " ", 1));
		else if (**str == '>')
			get_sympol_great(tokens, str);
		else if (**str == '<')
			get_sympol_less(tokens, str, &here);
		else if (**str == '|')
			add_token_last(tokens, PIPE, get_char(str, "|", 1));
		else if (**str == '$' && here == 0)
			add_token_last(tokens, DOLLAR, get_char(str, "$", 1));
		else
			get_token_utils(tokens, str, &here, &here2);
	}
}

t_token *tokenize(char *line)
{
    t_token *tokens = NULL;
    t_token *tmp;

    get_token(&tokens, &line);
    return (tokens);
}
