#include "../includes/minishell.h"

static int check_pairs1(char *s)
{
    int q;
    q = 0;
    // printf("%s", s);
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


void    check_pipe(token_t *c)
{
    token_t *tmp = NULL;
    tmp = c;
    while(tmp)
    {
        if(tmp->type == PIPE)
        {
            if(tmp->next == NULL)
            {
                printf("syntax pipe\n");
                break ;
            }
            else
            {
                handle_spaces2(tmp->next);
                break;
            }
             
        }
        tmp = tmp->next;
    }
    return ;
    
}

void check_newline(token_t *c)
{
    token_t *tmp = NULL;

    tmp = c;
    while(tmp)
    {
            if((tmp->type == LESS) || (tmp->type == GREAT) || (tmp->type == DGREAT) || (tmp->type == DLESS))
            {
                if(tmp->type == LESS)
                {
                    if(tmp->next != NULL && tmp->next->type == GREAT)
                    {
                        printf("newline2\n");
                    }
                    else 
                        printf("fcfvfvfv\n");
                    return ;
                }
                if(tmp->next == NULL)
                {
                    printf("3la slamtk\n");
                    break ;
                }
                else
                {
                    handle_spaces(tmp->next);
                    break;
                }       
            }
                
        tmp = tmp->next;
        }
}


void   handle_spaces(token_t *c)
{
    token_t *tmp = NULL;
    
    tmp = c;
    
    while(tmp && tmp->type == SPAACE)
        tmp = tmp->next;
    if(tmp == NULL)
        printf("newline 2\n");
    else if(is_other(tmp))
        printf("syntax error near unexpected token tmp\n");
    else
        printf("sent to redirections errors\n"); //word or quotes
    return ;
}

void   handle_spaces2(token_t *c)
{
    token_t *tmp = NULL;
    
    tmp = c;
    
    while(tmp && tmp->type == SPAACE)
        tmp = tmp->next;
    if(tmp == NULL || is_other(tmp))
        printf("syntax error near unexpected token tmp\n");
    else
        printf("sent to redirections errors\n"); //word or quotes
    return ;
}


int is_other(token_t *c)
{
    if(c->type == PIPE || c->type == LESS || c->type == DLESS || c->type ==DGREAT || c->type == WORD || c->type == DQUOTE || c->type == QUOTE)
        return (1);
    return (0);
}
