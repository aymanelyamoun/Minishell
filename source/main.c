
#include "../includes/minishell.h"


int main(int argc, char **argv, char **envp)
{
    char *line;
    token_t *tokens;
    char **arr;
    (void)argv;

    if(argc != 1)
        return 1;
    gen = malloc(sizeof(t_gen *));
    gen->env = env_create(envp); //TODO : put this in a function
    gen->pwd = getcwd(NULL, 0);
    //gen->envp = set_env(envp);
    handle_signals();
    while (1)
    {
        //line = ft_strdup("export HOME=davinci");
        line = readline("Minishell: ");
        if (!line)
             ctrld();
        else if (line && !*line)
        {
            free(line);
            continue ;
        }
        else if(line != NULL)
        {
            arr = ft_split(line, ' '); // imagining i have the splited commads 2d
            if(line != NULL && commands(arr) == YES)
                go_commands(arr);
            add_history(line);
            tokens = tokenize(line);
            syntax_err(tokens);  
        }
    }
    // free(line);
free_env(&gen->env);
return(0);
}
    

