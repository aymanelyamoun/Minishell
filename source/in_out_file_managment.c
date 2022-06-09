#include "../includes/minishell.h"
#include <fcntl.h>

int    open_file(token_t **tokens, int type)
{
    int fd;
	
	if (type == GREAT)
    	fd = open((*tokens)->next->data, O_RDWR | O_CREAT, 0777);
	else if (type == LESS)
    	fd = open((*tokens)->next->data, O_RDWR , 0777);
	else if (type == DGREAT)
    	fd = open((*tokens)->next->data, O_RDWR | O_CREAT | O_APPEND, 0777);
	else if (type == DLESS)
	{
		fd = heredoc(ft_strdup((*tokens)->next->data));
	}
	close(fd);
	return (fd);
}

void	check_file_direc_rm_token(token_t **tokens, t_cmd **cmds, int i)
{
	if ((*tokens)->prev == NULL)
		(*cmds)->tokens_cmd = (*tokens)->next->next;
	rm_token(&(*tokens)->next);
	rm_token(tokens);
		// printf("--- %s\n", (*tokens)->next->data);
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
            if (tokens->type == LESS || tokens->type == DLESS)
			{
                fd = open_file(&tokens, tokens->type);
				if ((*cmds)[i].infile != -1)
					close((*cmds)[i].infile);
				(*cmds)[i].infile = fd;
					// rm_token(&tokens);
					// rm_token(&tokens);
				check_file_direc_rm_token(&tokens, cmds, i);
				continue;
				// printf("--- %s\n", (tokens)->data);
			}
			else if (tokens->type == GREAT || tokens->type == DGREAT)
			{
                fd = open_file(&tokens, tokens->type);
				if ((*cmds)[i].outfile != -1)
					close((*cmds)[i].outfile);
				(*cmds)[i].outfile = fd;
					// rm_token(&tokens);
					// rm_token(&tokens);
				// printf("hi\n");
				check_file_direc_rm_token(&tokens, cmds, i);
				continue;
				// printf("--- %s\n", (tokens)->data);
			}
			tokens = tokens->next;
        }
        i++;
    }
    
}