#include "../includes/minishell.h"
#include <fcntl.h>

int    open_file(token_t **tokens, int type)
{
    int fd;
	
	if (type == GREAT)
    	fd = open((*tokens)->next->data, O_RDWR, 0777);
	else if (type == LESS)
    	fd = open((*tokens)->next->data, O_RDWR | O_CREAT, 0777);
	else if (type == DGREAT)
    	fd = open((*tokens)->next->data, O_RDWR | O_CREAT | O_APPEND, 0777);
	else if (type == DLESS)
	{
		fd = heredoc();
	}
	close(fd);
	return (fd);
}

void    check_file_direcitons(t_cmd **cmds, int pipes)
{
    int i;
    token_t *tokens;
	int	fd;

    i = 0;
    while (i <= pipes)
    {
        tokens = (*cmds)[i].tokens_cmd;
        while (tokens != NULL)
        {
            if (tokens->type == LESS || tokens->type == GREAT )
			{
                fd = open_file(&tokens, tokens->type);

			}
			else if (tokens->type == DLESS || tokens->type == DGREAT)
			{
                fd = open_file(&tokens, tokens->type);

			}
        }
        
    }
    
}