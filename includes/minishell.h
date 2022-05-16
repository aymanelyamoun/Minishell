/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufisaou <oufisaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:53:50 by oufisaou          #+#    #+#             */
/*   Updated: 2022/05/16 17:14:12 by oufisaou         ###   ########.fr       */
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
typedef enum type_s
{
    WORD,
    SEPARATOR,
    PIPE,
    REDIRECTION,
    
} type_t;

typedef struct token_s
{
    char *data;
    unsigned int type;
    struct token_s *next;
}token_t;

typedef struct cmd_s
{
    
    
} cmd_t;


#endif