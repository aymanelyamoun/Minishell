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

void    rm_spaces(token_t **tokens)
{
    token_t *tmp;
    int i = 0;

    while ((*tokens) != NULL && (*tokens)->type == SPACE)
    {
        rm_token(tokens);
        i++;
    }
    tmp = *tokens;
    while (tmp != NULL)
    {
        if (tmp->type == SPACE)
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
            if (tmp->next != NULL && tmp->next->type != SPACE && 
            (tmp->next->type == WORD || tmp->next->type == DQUOTE))
                play_with_tokens(&tmp, ft_strdup(tmp->next->data), env);
            if (tmp->next != NULL && tmp->next->type == SPACE)
                tmp->type = WORD;
        }
        tmp = tmp->next;
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
            rm_spaces(&tokens);
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
// t_cmd   *parsing(token_t *kokens)
// {
    
// }
