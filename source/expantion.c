/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufisaou <oufisaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:42:03 by ael-yamo          #+#    #+#             */
/*   Updated: 2022/06/02 21:09:06 by oufisaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft/libft.h"

//parsing steps
//call heardoc when you incounter it

// cerating the expander
// creating the minimizer


char    *find_value(char *str, char **env)
{
    int i;
    
    i = 0;
    while (env[i])
    {
        if (ft_strncmp(str, env[i], ft_strlen(str)) == 0)
            return (ft_strdup(&env[i][ft_strlen(str) + 1]));
        i++;
    }
    return (ft_strdup(""));
}

char	*rm_quotes(char *str, char c)
{
	int	i;
	char	*new;

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

char    *join_mix(token_t *token1, token_t *token2)
{
	if (token1->data[0] == '\"' || token1->data[0] == '\'')
	{
		token1->data = rm_quotes(token1->data, token1->data[0]);
	}
	if (token2->data[0] == '\"' || token2->data[0] == '\'')
	{
		token2->data = rm_quotes(token2->data, token2->data[0]);
	}
    return (ft_strjoin(token1->data, token2->data));
}

void    join_word(token_t **tokens)
{
    token_t *tmp;

    tmp = *tokens;
    while (tmp != NULL)
    {
        if (tmp->type == WORD || tmp->type == DQUOTE || tmp->type == QUOTE)
        {
            while ( tmp->next != NULL &&
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

void    rm_token(token_t **tokens)
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

void    rm_SPAACEs(token_t **tokens)
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

void    change_data(token_t **tokens, char *data)
{
    free((*tokens)->data);
    (*tokens)->data = data;
    (*tokens)->type = WORD;
}
void    play_with_tokens(token_t **tokens, char *str, char **env)
{
    char    *env_var;

    env_var = find_value(str, env);
    if ((*tokens)->next->type == WORD)
    {
        if (env_var != NULL)
        {
            change_data(tokens, env_var);
        }
    }
    else if ((*tokens)->next->type == DQUOTE)
    {
        free((*tokens)->data);
        (*tokens)->data = ft_strdup((*tokens)->next->data);
        (*tokens)->type = WORD;
    }
    rm_token(&((*tokens)->next));

}

void    expander(token_t **tokens, char **env)
{
    token_t *tmp;
    // char    **env = NULL;

    tmp = *tokens;
    while (tmp != NULL)
    {
        if (tmp->type == DOLLAR)
        {
            if (tmp->next != NULL && tmp->next->type != SPAACE && 
            (tmp->next->type == WORD || tmp->next->type == DQUOTE))
                play_with_tokens(&tmp, ft_strdup(tmp->next->data), env);
            if (tmp->next != NULL && tmp->next->type == SPAACE)
                tmp->type = WORD;
        }
        tmp = tmp->next;
    }
    
}

void    expander_in_quotes(token_t **token)
{
    char    *str;
    int     i;
    char    *final_quote;
	char	*tmp;

    str = (*token)->data;
    i = 0;
	final_quote
    while (str[i] != '\0')
    {
        if (str[i] == '$')
		{
			tmp = ft_substr(str, 0, i);
			ft_strjoin();
			get_var(str);
		}
    }
    
}

int main(int argc, char **argv, char **envp)
{
    char **env;
    char *line;
    token_t *tokens;
    token_t *tok;
    if(argc != 1)
        return (1);
    env = set_env(envp);
    while (1)
    {
        line = readline("ENTER PROMPT   ");
        if (line != NULL)
        {
            add_history(line);
            tokens = tokenize(line);
			tok = tokens;
            expander(&tokens, env);

            join_word(&tokens);
            rm_SPAACEs(&tokens);
            while (tokens != NULL)
            {
                printf("from main : -- %d ---> %s\n", tokens->type, tokens->data);
                tokens = tokens->next;
            }
            
        }
		else
			exit(0); //last status
    }
    return (0);
}

// tastks : 
// add the expantion to vars inside DQUOTE

// t_cmd   *parsing(token_t *kokens)
// {
    
// }
