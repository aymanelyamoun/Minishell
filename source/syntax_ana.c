/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_ana.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-yamo <ael-yamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 11:18:11 by oufisaou          #+#    #+#             */
/*   Updated: 2022/06/02 21:42:53 by ael-yamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int    check_quotes(token_t *tmp)
{
    size_t index;
    static int squote;
    static int dquote;
    token_t *c = tmp;

    index = 0;
    squote = 0;
    dquote = 0;
    while(c)
    {
        while(index < ft_strlen(c->data))
        {
            if(c->data[index] == '\'')
                squote += 1;
            if(c->data[index] == '\"')
                dquote += 1;
            index++;
        }
        index = 0;
        c = c->next;
    }
    printf(" dquote : %d\n", dquote);
    squote = squote % 2;
    dquote = dquote % 2;
    if(squote != 0 || dquote != 0)
    {
       error_free("QUOTES", c);
       return (0);
    }
    return 1;
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
                    if(tmp->next->type == GREAT)
                    {
                        printf("newline2\n");
                        return ;
                    }
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
