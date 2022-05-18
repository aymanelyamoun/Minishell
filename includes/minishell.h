/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-yamo <ael-yamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:53:50 by oufisaou          #+#    #+#             */
/*   Updated: 2022/05/18 19:58:41 by ael-yamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
# include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
// # include "./libft/libft.h"

//every constant is equal to its position in enum
typedef enum type_s
{
    WORD,
    QUOTE,
    DQUOTE,
    BACKSLASH,
    SPACE,
    NEWLINE,
    GREAT,
    DGREAT,
    LESS,
    DLESS,
    PIPE,
    DOLLAR
} type_t;

//    WORD,
//the linked list to store the tokens

typedef struct token_s
{
    char *data;
    unsigned int type;
    struct token_s *next;
    struct token_s *prev;
}token_t;

// typedef struct cmd_s
// {
    
    
// } cmd_t;

/*********************************/
/********** TOKENS LIST **********/
/*********************************/

token_t *new_token(unsigned int type, char *data);
void	add_at_end(token_t *tokens_head, token_t *token);
void	add_token_last(token_t *token_head, unsigned int type, char *data);

#endif