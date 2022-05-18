#include <readline/readline.h>
#include "../includes/minishell.h"



token_t *tokenize(char *line)
{
    int i;
    token_t *tokens;

    i = 0;
    while (line[i])
    {

    }
    
}

int main(void)
{
    char *line;

    while (1)
    {
        line = readline("ENTER PROMPT   ");
        if (line != NULL)
        {
            add_history(line);
        }
    }
    return (0);
}