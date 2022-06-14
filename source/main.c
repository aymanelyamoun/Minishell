
#include "../includes/minishell.h"

t_gen *gen;

void main(int argc, char **argv, char **envp)
{
    char *line;
    token_t *tokens;
    char **arr;

    if(argc != 1)
        return ;
    gen = malloc(sizeof(t_gen*));
    gen->env = env_create(envp);
    //gen->envp = set_env(envp);
    // handle_signals();
    while (1)
    {
        line = readline("Minishell: ");
        if (!line)
        {
            printf("exit\n");
            break ;
        }
        else if(line != NULL)
        {
            arr = ft_split(line, ' '); //imagining i have the splited commads 2d
            // if(line != NULL && commands(arr) == YES)
            //     go_commands(gen, arr);
            add_history(line);
            tokens = tokenize(line);
            syntax_err(tokens);  
        }
    }
    // free(line);
    // free_env(&gen->env);

}
    

