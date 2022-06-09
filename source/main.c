
#include "../includes/minishell.h"

t_gen *gen;

int main(int argc, char **argv, char **envp)
{
    char *line;
    token_t *tokens;
    char **arr;
    char envvp;

    if(argc != 1)
        return (1);
    gen = malloc(sizeof(t_gen*));
    gen->env = env_create(envp);
    gen->envp = set_env(envp);
    handle_signals();
    while (1)
    {
        line = readline("Minishell: ");
        if (!line)
             ctrld(); // should be fixed here
        else if(line != NULL)
        {
            arr = ft_split(line, ' '); //imagining i have the splited commads 2d
            if(line != NULL && commands(arr) == YES)
                    go_commands(gen, arr);
            add_history(line);
            tokens = tokenize(line);
            if(check_quotes(tokens) == 1) //problem here accesiing some kind of memory it prints trash
            {
                check_pipe(tokens);
                check_newline(tokens);
            }
        }
        else
            continue ;
    }
    return (0);
}
    

