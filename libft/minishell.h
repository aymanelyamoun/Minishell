/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-yamo <ael-yamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:53:50 by oufisaou          #+#    #+#             */
/*   Updated: 2022/05/24 21:42:06 by ael-yamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
# include "./libft/libft.h"
# include <termios.h>
# include <signal.h>
// # include "./libft/libft.h
//every constant is equal to its position in enum
typedef enum type_s
{
    WORD,
    QUOTE,
    DQUOTE,
    // BACKSLASH,
    SPACE,
    // NEWLINE,
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

<<<<<<< HEAD:includes/minishell.h
// typedef struct shell_s
// {
// }
    
=======
// typedef struct s_gen
// {

>>>>>>> 310e4d91931bcadc3785da201adf34230f87f70f:libft/minishell.h

// }t_gen;
/*********************************/
/********** TOKENS LIST **********/
/*********************************/

token_t *new_token(unsigned int type, char *data);
void	add_at_end(token_t **tokens_head, token_t *token);
void	add_token_last(token_t **token_head, unsigned int type, char *data);
char **set_env(char **envp);
void    handler(int sig);
void handle_signals(void);
void    terminal_settings(void);

token_t *tokenize(char *line);
void    get_token(token_t **tokens, char **str);

void	get_sympol_less(token_t **tokens, char **str);
void	get_sympol_great(token_t **tokens, char **str);
char *get_char(char **str, char *c, int increment);
int	get_word(char **str, char c);
int	get_quote(char **str, char c);



#endif