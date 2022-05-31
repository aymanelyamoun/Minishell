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
    return (NULL);
}

// void    rm_token(token_t **tokens)
// {
//     token_t *tmp;

//     if (*tokens == NULL)
//         return ;
// 	if ((*tokens)->prev == NULL && (*tokens)->next == NULL)
// 	{
// 		tmp = *tokens;
// 		(*tokens) = NULL; 
// 	}

//     if ((*tokens)->prev == NULL)
//     {
//         tmp = *tokens;
// 		(*tokens)->next->prev = NULL;
//         (*tokens) = (*tokens)->next;
//         // free(tmp);
//     }
// 	else if ((*tokens)->next == NULL)
// 	{
// 		tmp = *tokens;
// 		(*tokens)->prev->next = NULL;
// 		// (*tokens)->next->prev = (*tokens)->prev;
// 	}
// 	else
// 	{
// 		tmp = *tokens;
// 		(*tokens)->prev->next = (*tokens)->next;
// 		(*tokens)->next->prev = (*tokens)->prev;
// 		(*tokens) = (*tokens)->next;
// 	}
// 	free(tmp);
// }

// void	free_nodes(token_t **tokens)
// {
// 	token_t *tmp;

// 	// while (*tokens != NULL)
// 	// {
// 		tmp = (*tokens)->next;
// 		free((*tokens)->data);
// 		free((*tokens));
// 		(*tokens) = tmp;
// 		free((*tokens)->data);
// 		free((*tokens));
// 	// }
// }

void	add_to_tokens(token_t **tokens, token_t **token)
{
	token_t *tmp;

    if ((*tokens) == NULL)
        (*tokens) = *token;
    if ((*tokens)->prev == NULL)
    {
        (*token)->next = (*tokens);
        (*tokens)->prev = *token;
    }
    else
    {
        (*token)->next = (*tokens);
        (*token)->prev = (*tokens)->prev;
        (*tokens)->prev->next = (*token);
        (*tokens)->prev = *token;
    }
}

void    rm_token(token_t **tokens, token_t *token)
{
    if (token->prev == NULL && token->next == NULL)
    {
        *tokens = NULL;
    }
    if (token->prev == NULL)
    {
        *tokens = token->next;
        // (*tokens) = (*tokens)->prev;
    }
    if (token->next == NULL)
    {
        (*tokens)->prev->next = NULL;
        *tokens = (*tokens)->prev;
    }
    else
    {   
        (*tokens)->next->prev = token->prev;
        (*tokens)->prev->next = token->next;
        (*tokens) = (*tokens)->next;
    }
    free(token);
}
// void    rm_token(token_t **tokens, token_t *token)
// {
//     if (token->prev == NULL && token->next == NULL)
//     {

//         *tokens = NULL;
//     }
//     if (token->prev == NULL)
//     {
//         *tokens = token->next;
//         printf("%s  0\n", token->data);
//         // (*tokens) = (*tokens)->prev;
//     }
//     if (token->next == NULL)
//     {
//         (*tokens)->prev->next = NULL;
//         // (*tokens) = (*tokens)->prev;
//         printf("%s  1\n", (*tokens)->data);
//     }
//     else
//     {
//         // printf("%s  2\n", token->data);
//         (*tokens)->next->prev = token->prev;
//         (*tokens)->prev->next = token->next;
//         (*tokens) = (*tokens)->prev;
//     }
//     free(token);
// }

void    play_with_tokens(token_t **tokens, char *str, char **env)
{
    char    *env_var;
    token_t *token;

    env_var = find_value(str, env);
    if (env_var != NULL)
    {
        token = new_token(WORD, env_var);
		add_to_tokens(tokens, &token);
    }
    rm_token(tokens, *tokens);
    rm_token(tokens, *tokens);

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
            if (tmp->next != NULL && tmp->next->type != SPACE && tmp->next->type == WORD)
                play_with_tokens(&tmp, ft_strdup(tmp->next->data), env);
            if (tmp->next != NULL && tmp->next->type != SPACE && tmp->next->type == DQUOTE)
                rm_token(&tmp, tmp);
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
			// while (tok != NULL)
            // {
    		// 	printf("from main : -- %d ---> %s\n", tok->type, tok->data);
            //     tok = tok->next;
            // }
            expander(&tokens, env);
			// rm_token((tokens));
			// rm_token((tokens->next));
			// rm_token((tokens->next));
			// printf("____________\n");
			// rm_token((tokens->next));
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
