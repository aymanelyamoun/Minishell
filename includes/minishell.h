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
#include <string.h>
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
    int exec;
} t_cmd;

typedef struct s_gen
{
    int exit_status;
    t_list *env;
    char **envp;
    char *pwd;
} t_gen;

t_gen *gen;
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
void error_free(char *str, token_t *tokens);
void free_all(token_t *tokens);
int check_redirection(token_t *c);
int check_newline(token_t *c);

int is_other(token_t *c);
t_list *env_create(char **envp);
int handle_spaces(token_t *c);
int check_pipe(token_t *c);
int handle_spaces2(token_t *c);
 int ctrld(void);

////////////////////////////////////////////////
char    *find_value(char *str, t_list *env_l);
char *join_mix(token_t *token1, token_t *token2);
void join_word(token_t **tokens);
void rm_token(token_t **tokens);
void rm_spaces(token_t **tokens);

void	free_all(token_t *tokens);
int    check_newline(token_t *c);
// int ctrld(void);
int is_other(token_t *c);
t_list *env_create(char **envp);

/*********************************/
/********* EXPANTION *********/
/*********************************/

char *get_var(char **str, char *final_quote, t_list *env);
char *join(char *final_quote, char *tmp);
/*********************************/
/********* CMD MANAGMENT *********/
/*********************************/

int count_pipes(token_t *tokens);
//static t_cmd *creat_cmds_utils(token_t **tokens, t_cmd **cmds); unused function error
t_cmd *creat_cmds(token_t **tokens);
int	get_cmds_path(t_cmd **cmds, int pipes, t_list *env_l);

/*********************************/
/******** FILE MANAGMENT *********/
/*********************************/

int	ft_strcmp(char *s1, char *s2);
int heredoc(char *limiter);
void check_file_direcitons(t_cmd **cmds, int pipes);
void rm_redirecitons(t_cmd **cmds, int pipes);

/*********************************/
/******** PIPE MANAGMENT *********/
/*********************************/

int     **creat_pipes(int pipes_num);
void	close_pipes(int **pipes, int count);
void	free_pipes(int **pipes, int pipes_num);
void	assign_pipes(int **pipes, t_cmd **cmds, int pipes_num);
void    execution(t_cmd *cmds, int pipes_num);

/*********************************/
/*********Builtins****************/
/*********************************/

int	ft_cd(char **path);
void	cd_home(t_gen *gen);
void	ft_echo(char **str) ;
void	ft_env(void);
int ft_exit(char **arg);
void	ft_pwd(void);
int syntax_err(token_t *token);
int change_env(char *p);
int    modify_env(char *path);

int check_double(token_t *tmp);
int check_inside(token_t *c);
void check_one(token_t *tmp);
int check_inside2(token_t *tmp);
int is_other2(token_t *c);
void    go_commands(char **line);
int commands(char **line);
char *ft_strjoin_free(char const *s1, char const *s2);
int ft_add_list(t_list **alst, char *str);
void    free_env(t_list **env);
int	ft_strlen2(char **str);
char *join_str(char const *s1, char const *s2);

////////////////////////////////////////////////
int ft_export(char **next);
int check_arg(char *next);
void  print_err_exp(char *next);
void	free_split(char **array);
void	print_export(t_list *env);

int ft_unset(char **next);
int check_arg2(char *next);
int start_unset(t_list *env, char *next);
int ft_strchr1(const char *str, int n);
int is_alone(char *s);
int len_list(t_list **list);
int set_flag(char *s);

char **convert_array(t_list **env);
long long	ft_atoll(const char *dest);
int check_valid(char *next);
int is_long(char *next);
#endif