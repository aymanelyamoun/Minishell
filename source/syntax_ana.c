/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_ana.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufisaou <oufisaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 11:18:11 by oufisaou          #+#    #+#             */
/*   Updated: 2022/06/02 16:28:58 by oufisaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    check_quotes(token_t *tmp)
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
    squote = squote % 2;
    dquote = dquote % 2;
    if(squote != 0 || dquote != 0)
    {
       error_free("QUOTES", c);
    }
    return ;
}

//&& (tmp->data[index + 1] == '\0' || tmp->data[index + 1] == '\n')

//case 1: > or < alone or not followed by anything , it gives error newline
//case 3: > or < followed by a space, it calls a function to handle redirection
//case 4: > or < followed by a word, it calls a function to handle redirection
//case 5: it should not be followed by any operator. it gives error
//case 6: still need to handle the pipes
//&& tmp->data && tmp->data[index + 1] != '>' && tmp->data[index + 1] != '<')
// void    check_newline(token_t *c)
// {
//     token_t *tmp = NULL;
//     size_t index;

//     tmp = c;
//     index = 0;
//     while(tmp)
//     {
//         while(index < ft_strlen(tmp->data))
//         {
//             while(tmp->type == SPACE)
//                 tmp = tmp->next;
//             if(tmp->next == NULL)
//             {
//                 if (tmp->data[index] == '>' || (tmp->data[index + 1] == '>'))
//                 {
//                     printf("parse error near to newline\n");
//                     break;
//                 }
//                 else if (tmp->data[index] == '<' || (tmp->data[index + 1] == '<' && tmp->data[index + 1] != '>'))
//                 {
//                     printf("parse error near to newline\n");
//                     break ;
//                 }
//             }
//             else if (tmp->next != NULL)
//             {
//                 while(tmp->next->type == SPACE)
//                     tmp = tmp->next;
//                 if (tmp->data[index] ==  '>')
//                 {
//                     if(tmp->data[index + 1] == '<' || tmp->data[index + 1] == '<')
//                 }
//                     if(tmp->next->type == LESS || tmp->next->type == GREAT || tmp->next->type == DGREAT || tmp->next->type == DLESS)
//                 printf("syntax error near to operator\n");
//             }
            
//             index++;
//         }
//         index = 0;
//         tmp = tmp->next;
//     }
//     return ;
// }





void check_newline(token_t *c)
{
    token_t *tmp = NULL;
    size_t index;

    tmp = c;
    index = 0;
while(tmp)
{
        while(index < ft_strlen(tmp->data))
        {
            if(tmp->next == NULL)
            {
                if(ft_strncmp(tmp->data + index, ">", 1) == 0 || ft_strncmp(tmp->data + index, "<", 1) == 0|| ft_strncmp(tmp->data + index, ">>", 2) == 0 || ft_strncmp(tmp->data + index, "<<", 2) == 0)
                {
                    printf("parse error near to newline\n");
                    break ;
                }
            }
            index++;
        }
        tmp = tmp->next;
    }
    return ;  
}
//     void    check_newline(token_t *c)
// {
//     token_t *tmp = NULL;
//     size_t index;

//     tmp = c;
//     index = 0;
//     while(tmp)
//     {
//         while(tmp->next->type == SPACE)
//              tmp = tmp->next;
//         while(index < ft_strlen(tmp->data))
//         {
//             if(tmp->next == NULL)
//             {
//                 if (tmp->data[index] == '>')
//                 {
//                     if(tmp->data[index + 1] != '\0')
//                         while(tmp->next->type == SPACE && tmp)
//                              tmp = tmp->next;
//                     printf("parse error near to newline hani\n");
//                     break;
//                 }
//                 else if (tmp ->data[index] == '>' && (tmp->data[index + 1] == '>'))
//                 {
//                    printf("parse error near to newline\n");
//                     break;
//                 }
//                 else if (tmp->data[index] == '<' || (tmp->data[index + 1] == '<' && tmp->data[index + 1] != '>'))
//                 {
//                     printf("parse error near to newline rf\n");
//                     break ;
//                 }
//             }
//                 // else if (tmp->data[index] == '|')
//                 // {
//                 //     printf("parse error in pipe\n");
//                 //     break;
//                 // }
            
//             // else if (tmp->next != NULL)
//             // {
//             //     while(tmp->next->type == SPACE)
//             //         tmp = tmp->next;
//             //     if (tmp->data[index] ==  '>')
//             //     {
//             //         if(tmp->data[index + 1] == '<')
//             //             printf("syntax error near to newline\n");
//             //     }
//                 //     if(tmp->next->type == LESS || tmp->next->type == GREAT || tmp->next->type == DGREAT || tmp->next->type == DLESS)
//                 // printf("syntax error near to operator\n");
            
            
//             index++;
//         }
//         index = 0;
//         tmp = tmp->next;
//     }

// }



// void    check_redirection(token_t *c)
// {
//     token_t *tmp = NULL;
//     tmp = c;
//     while(tmp)
//     {
//         if((tmp->next != NULL) && (tmp->type == LESS || tmp->type == GREAT || tmp->type == DGREAT || tmp->type == DLESS))
//         {
//             while(tmp->next->type == SPACE)
//                 tmp = tmp->next;
//             if(tmp->next->type == WORD)
//                 printf("send to redirection\n");
//             else
//                 return ;
//         }
//         tmp = tmp->next;
//     }
//     return ;
// }

// void    check_operators(token_t *c)
// {
//     token_t *tmp = NULL;
    
//     tmp = c;
//     while(tmp)
//     {
//          if((tmp->type == LESS || tmp->type == GREAT || tmp->type == DGREAT || tmp->type == DLESS ||  tmp->type == PIPE))
//          {
//                 while(tmp->next->type == SPACE)
//                     tmp = tmp->next;
//                 if(tmp->type == LESS || tmp->type == GREAT || tmp->type == DGREAT || tmp->type == DLESS ||  tmp->type == PIPE)
//                     printf("syntax error near to: 'operator'\n");
//                 return ;
//         }
//         // else if (tmp->type == PIPE)
//         // {
//         //     while(tmp->next->type == SPACE)
//         //         tmp = tmp->next;
//         //     if(tmp->next->type == WORD)
//         //         printf("send to pipe\n");
//         //     else
//         //         return ;
         
//          tmp = tmp->next;  
//     }
// }