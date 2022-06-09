
#include "../includes/minishell.h"

t_list *env;

// int main(int argc, char **argv, char **envp)
// {
//     char *line;
//     token_t *tokens;

//     if(argc != 1)
//         return (1);
//     env = env_create(envp);
//     handle_signals();
//     while (1)
//     {
//         line = readline("Minishell: ");
//         if(!line)
//             ctrld(&env); //there is a seg fault here
//         else if(line != NULL && commands(line) == YES)
//             go_commands(env, line);
//         else
//         {
//             add_history(line);
//             tokens = tokenize(line);
//             //ft_echo(argc, argv);
//             if(check_quotes(tokens) == 1)
//             {
//                 check_pipe(tokens);
//                 check_newline(tokens);
//             }
//             else
//                 continue ;
//         }
//     }
//     return (0);
// }
    

