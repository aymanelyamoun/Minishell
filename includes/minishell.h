/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufisaou <oufisaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:53:50 by oufisaou          #+#    #+#             */
/*   Updated: 2022/05/16 19:45:49 by oufisaou         ###   ########.fr       */
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
# include "./libft/libft.h"
# include <termios.h>
# include <signal.h>
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

//the linked list to store the tokens

typedef struct token_s
{
    char *data;
    unsigned int type;
    struct token_s *next;
}token_t;

typedef struct shell_s
{
    

} shell_t;

#endif