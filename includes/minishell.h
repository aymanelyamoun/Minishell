#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <termios.h>
#include <signal.h>
#include <fcntl.h>
#include "../includes/libft/libft.h"

#define YES 1
#define NO 0
#define PATH_MAX 4096

typedef enum type_s
{
    WORD,
    QUOTE,
    DQUOTE,
    SPAACE,
    GREAT,
    DGREAT,
    LESS,
    DLESS,
    PIPE,
    DOLLAR
} type_t;

typedef struct token_s
{
    char *data;
    char *old_data;
    unsigned int type;
    struct token_s *next;
    struct token_s *prev;
} token_t;

typedef struct s_cmd
{
    char *cmd_path;
    char **cmd_args;
    int infile;
    int outfile;
    token_t *tokens_cmd;
    int pipes;
} t_cmd;

typedef struct s_gen
{
    int exit_status;
    t_list *env;
    char **envp;

} t_gen;

/*********************************/
/********** TOKENS LIST **********/
/*********************************/

token_t *new_token(unsigned int type, char *data);
void add_at_end(token_t **tokens_head, token_t *token);
void add_token_last(token_t **token_head, unsigned int type, char *data);
void rm_token(token_t **tokens);

char **set_env(char **envp);
void handler(int sig);
int handle_signals(void);
int terminal_settings(void);

token_t *tokenize(char *line);
void get_token(token_t **tokens, char **str);

void get_sympol_less(token_t **tokens, char **str);
void get_sympol_great(token_t **tokens, char **str);
char *get_char(char **str, char *c, int increment);
int get_word(char **str);
int get_quote(char **str, char c);
int check_quotes(token_t *c);
token_t *error_free(char *str, token_t *tokens);
void free_all(token_t *tokens);

int is_other(token_t *c);
t_list *env_create(char **envp);
int ctrld(void);


char *find_value(char *str, char **env);

void check_redirection(token_t *c);
int check_newline(token_t *c);
void check_operators(token_t *c);
int is_other(token_t *c);
t_list *env_create(char **envp);
int handle_spaces(token_t *c);
int check_pipe(token_t *c);
int handle_spaces2(token_t *c);
int syntax_err(token_t *token);
// int ctrld(void);

////////////////////////////////////////////////
char    *find_value(char *str, t_list *env_l);

char *join_mix(token_t *token1, token_t *token2);
void join_word(token_t **tokens);
void rm_token(token_t **tokens);
void rm_spaces(token_t **tokens);

void	free_all(token_t *tokens);

int    check_newline(token_t *c);
int ctrld(void);
int    check_operators(token_t *c);
int is_other(token_t *c);
t_list *env_create(char **envp);
int   handle_spaces(token_t *c);
int    check_pipe(token_t *c);
int   handle_spaces2(token_t *c);

void    check_redirection(token_t *c);
// void    check_newline(token_t *c);
// int ctrld(void);
void    check_operators(token_t *c);
int is_other(token_t *c);
t_list *env_create(char **envp);
// void   handle_spaces(token_t *c);
// void    check_pipe(token_t *c);
// void   handle_spaces2(token_t *c);


/*********************************/
/********* CMD MANAGMENT *********/
/*********************************/

int count_pipes(token_t *tokens);
static t_cmd *creat_cmds_utils(token_t **tokens, t_cmd **cmds);
t_cmd *creat_cmds(token_t **tokens);
int	get_cmds_path(t_cmd **cmds, int pipes, t_list *env_l);

/*********************************/
/******** FILE MANAGMENT *********/
/*********************************/

int heredoc(char *limiter);
void check_file_direcitons(t_cmd **cmds, int pipes);
void rm_redirecitons(t_cmd **cmds, int pipes);

/*********************************/
/*********Builtins****************/
/*********************************/

void ft_echo(t_gen *gen, char **str);
int is_flag(char *str);
void ft_env(t_list *env);
void free_env(t_list **env);
int	array_len(char **array);
int	ft_strcmp(char *s1, char *s2);
void	print_cwd(void);
void	go_oldpwd(t_gen *gen);
int    ft_cd(t_gen *gen, char *path);
char *change_env(t_gen *gen, char *new);


int check_pairs2(char *s);
int	commands(char **line);
void	go_commands(t_gen *gen, char **line);
int	array_len(char **array);
int	ft_strcmp(char *s1, char *s2);


////////////builtins/////////////////
int	ft_cd(t_gen *gen, char *path);
void	cd_home(t_gen *gen);
void	ft_echo(t_gen *gen, char **str) ;
void	ft_env(t_list *env);
int ft_exit(t_list **env, char **arg);
char *ft_pwd(t_gen *gen);
int syntax_err(token_t *token);
char*    change_env2(t_gen *gen);
void    modify_env(t_list *gen, char *arr);

int check_double(token_t *tmp);
int check_inside(token_t *c);
#endif
