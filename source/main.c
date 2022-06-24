
#include "../includes/minishell.h"


int main(int argc, char **argv, char **envp)
{
    char *line;
    token_t *tokens;
    char **arr;
    (void)argv;

    int i=0;
    if(argc != 1)
        return 1;
    gen = ft_calloc(sizeof(t_gen *), 1);
    gen->pwd = getcwd(NULL, 0);
    gen->env = env_create(envp); //TODO : put this in a function

    handle_signals();
    while (1)
    {
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
            free_split(arr);
            add_history(line);
            // tokens = tokenize(line);
            // syntax_err(tokens);  
        }
        free(line);
    }
return(0);
}
    

char **convert_array(t_list **env)
{
    int index;
    int size;
    char **arr;
    t_list *tmp;
 
    size = len_list(env);
    
    tmp = *env;
    arr = (char **)malloc(sizeof(char *) * size + 1);
    index = 0;
    while(tmp->next)
    {
        arr[index] = tmp->content;
        tmp = tmp->next;
        index++;
    }
    return (arr);
}