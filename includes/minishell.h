/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufisaou <oufisaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:53:50 by oufisaou          #+#    #+#             */
/*   Updated: 2022/06/01 12:27:20 by oufisaou         ###   ########.fr       */
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
# include "../includes/minishell.h"
# include <termios.h>
# include <signal.h>
# include "../includes/libft/libft.h"


typedef enum type_s
{
    WORD,
    QUOTE,
    DQUOTE,
    SPACE,
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

typedef struct env_outil_s
{
    char *data; //data after =
    char *name; //name of env var
    struct env_s *next_env; //next env
}env_outil_t;

typedef struct env_s
{
    env_outil_t envi; //the enviroment variable structure
    int shlvl; //the increnented value in env
} env_t;

typedef struct s_gen
{
    env_t env;
    int status;
    char *read;
}t_gen;

t_gen envi;  //this global variable has the variables that we use inmultiple files at once

// typedef struct shell_s
// {
// }
   

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
int	get_word(char **str);
int	get_quote(char **str, char c);
void    check_quotes(token_t *c);
int tokensize(token_t *token);
token_t *error_free(char *str, token_t *tokens);
void	free_all(token_t *tokens);
int ft_strchr1(char *str, int c);

#endif