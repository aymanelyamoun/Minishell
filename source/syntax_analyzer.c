#include "../includes/minishell.h"

static int check_pairs1(char *s)
{
    int q;
    q = 0;
    while(*s)
    {
        if (q == 0 && (*s == '\"' || *s =='\''))
        {
            if(*(s++) == '\'')
                q = 2;
            else
                q = 3;
        }
        while(*s && ((q == 3 && *s != '\"') || (q == 2 && *s != '\'')))
            s++;
        if((q == 3 && *s == '\"') || (q == 2 && *s == '\''))
            q = 0;
        s++;
    }
    return (!q);
}

int check_quotes(token_t *token)
{
    token_t *tmp;
    char *s;
    tmp = token;
    
    while(tmp)
    { 
        s = tmp->data;
        if(!check_pairs1(s))
        {
            printf("unclosed quote\n");
            return (0);
        }
        tmp = tmp->next;
    }
    return (1);
}

int    check_pipe(token_t *c)
{
    token_t *tmp = NULL;
    tmp = c;

    if(tmp->type == PIPE)
    {
        if(tmp->next == NULL)
        {
            printf("syntax pipe 2\n");
            return (0);
        }
        else
        {
            handle_spaces2(tmp->next);
        } 
    }
    while(tmp->next)
        tmp = tmp->next;
    if(tmp->type == PIPE)
    {
        if(tmp && tmp->next == NULL)
        {
            printf("syntax pipe\n");
            return (0);
        }
        else
        {
            handle_spaces2(tmp->next);
        } 
    }
    return (1);
}

int check_inside(token_t *tmp)
{
    if (tmp && tmp->type == PIPE)
    {
        printf("error first pipe\n");
        return (0);
    }
       
    while(tmp)
    {
        if(tmp->type == PIPE)
        {
            tmp = tmp->next;
            if (tmp == NULL)
                return (0);
            while(tmp && tmp->type == SPAACE)
              tmp = tmp->next;
            if(tmp && tmp->type == PIPE)
            {
                printf("pipe error in check_pipe\n");
                return (0);
            }
        }
        tmp = tmp->next;
    }
    return (1);
}


int check_newline(token_t *c)
{
    token_t *tmp = NULL;

    tmp = c;
    while(tmp)
    {
        if((tmp->type == LESS) || (tmp->type == GREAT) || (tmp->type == DGREAT) || (tmp->type == DLESS))
        {
            tmp = tmp->next;
           while(tmp && tmp->type == SPAACE)
                tmp = tmp->next;
            if(tmp && is_other2(tmp))
            {
                printf("error successif operators %s\n", tmp->data);
                return(0);
            }
            else if (tmp == NULL)
            {
                printf("redirection symbol alone!\n");
                return(0);
            }
        }
        tmp = tmp->next;
    }
    return (1);
}
int   handle_spaces(token_t *c)
{
    token_t *tmp = NULL;
    
    tmp = c;
    
    while(tmp && tmp->type == SPAACE)
        tmp = tmp->next;
    if(tmp == NULL)
    {
        printf("newline 2\n");
        return (0);
    }
    else if(is_other(tmp))
    {
         printf("syntax error near unexpected token tmp 2\n");
         return (0);
    }  

    return (1);
}

int   handle_spaces2(token_t *c)
{
    token_t *tmp = NULL;
    
    tmp = c;
    
    while(tmp && tmp->type == SPAACE)
        tmp = tmp->next;
    if((tmp == NULL || is_other(tmp)))
    {
        printf("syntax error near unexpected token tmp 1\n");
        return (0);
    }   
    return (1);
}


int is_other(token_t *c)
{
    if(c->type == LESS || c->type == DLESS || c->type ==DGREAT  || c->type == DQUOTE || c->type == QUOTE)
        return (1);
    return (0);
}

int syntax_err(token_t *token)
{
    // if (check_inside(token) == 1)
    //     return (1);
    if(check_quotes(token) == 1 && check_newline(token) == 1 && check_pipe(token) == 1 && check_inside(token) == 1)
        return (1);
    return (0);
}


int is_other2(token_t *c)
{
    if(c->type == LESS || c->type == DLESS || c->type ==DGREAT || c->type == GREAT || c->type == PIPE)
        return (1);
    return (0);
}

