#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/types.h>
# include <termios.h>
# include <signal.h>
# include <string.h>
# include <fcntl.h>
# include "../includes/libft/libft.h"

# define YES 1
# define NO 0
# define PATH_MAX 4096

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
}	t_type;

typedef struct token_s
{
	char *data;
	char *old_data;
	unsigned int type;
	struct token_s *next;
	struct token_s *prev;

} t_token;

typedef struct s_cmd
{
	char *cmd_path;
	char **cmd_args;
	int infile;
	int outfile;
	t_token *tokens_cmd;
	int exec;
} t_cmd;

typedef struct s_gen
{
	int exit_status;
	t_list *env;
	char **envp;
	char *pwd;
} t_gen;

t_gen gen;
/*********************************/
/********** TOKENS LIST **********/
/*********************************/

t_token *new_token(unsigned int type, char *data);
void add_at_end(t_token **tokens_head, t_token *token);
void add_token_last(t_token **token_head, unsigned int type, char *data);
void rm_token(t_token **tokens);

char **set_env(char **envp);
void handler(int sig);
int handle_signals(void);
int terminal_settings(void);

t_token *tokenize(char *line);
void get_token(t_token **tokens, char **str);

void get_sympol_less(t_token **tokens, char **str);
void get_sympol_great(t_token **tokens, char **str);
char *get_char(char **str, char *c, int increment);
int get_word(char **str);
int get_quote(char **str, char c);
int check_quotes(t_token *c);
void error_free(char *str, t_token *tokens);
void free_all(t_token *tokens);
int check_redirection(t_token *c);
int check_newline(t_token *c);
char    *str_to_lower(char *str);

int is_other(t_token *c);
t_list *env_create(char **envp);
int handle_spaces(t_token *c);
int check_pipe(t_token *c);
int handle_spaces2(t_token *c);
int ctrld(void);

////////////////////////////////////////////////
char    *find_value(char *str, t_list *env_l);
char *join_mix(t_token *token1, t_token *token2);
void join_word(t_token **tokens);
void rm_token(t_token **tokens);
void rm_spaces(t_token **tokens);

void	free_all(t_token *tokens);
int    check_newline(t_token *c);
// int ctrld(void);
int is_other(t_token *c);
t_list *env_create(char **envp);
char **convert_to_array(t_list **env);

/*********************************/
/*********** EXPANTION ***********/
/*********************************/

char *get_var(char **str, char *final_quote, t_list *env);
char *join(char *final_quote, char *tmp);
/*********************************/
/********* CMD MANAGMENT *********/
/*********************************/

int count_pipes(t_token *tokens);
static t_cmd *creat_cmds_utils(t_token **tokens, t_cmd **cmds);
t_cmd *creat_cmds(t_token **tokens);
int	get_cmds_path(t_cmd **cmds, int pipes);

/*********************************/
/******** FILE MANAGMENT *********/
/*********************************/

int	ft_strcmp(char *s1, char *s2);
int heredoc(char *limiter, int *exit_status);
// int heredoc(char *limiter);
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
void	cd_home(t_gen gen);
void	ft_echo(char **str) ;
void	ft_env(void);
int ft_exit(char **arg);
void	ft_pwd(void);
int syntax_err(t_token *token);
int change_env(char *p);
int    modify_env(char *path);
int is_buit_in(char *cmd);

int check_double(t_token *tmp);
int check_inside(t_token *c);
void check_one(t_token *tmp);
int check_inside2(t_token *tmp);
int is_other2(t_token *c);
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
// int len_list(t_list **list);
int set_flag(char *s);

char **convert_array(t_list **env);
long long	ft_atoll(const char *dest);
int check_valid(char *next);
int is_long(char *next);
void  print_err_uns(char *next);
char *ft_to_lower(char *str);
int append_case(t_list **env_list, char *str);
int append_it(t_list **env_list, char *str);
int find_plus(char *str);
void	ft_sort(t_gen *gen);

int	len_list(t_list **list);
t_list	*swap(t_list *ptr1, t_list *ptr2);
void	bubbleSort(t_list **head, int count);
int print(char *s);
int	small(char **p);
int	small2(char **p);
int	small3(char **pwd);
int	s1(char *str);
int	s2(char *str);
void	suite(char **str);
int    has_equal(char *str);
#endif