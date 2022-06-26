#include "../includes/minishell.h"
#include <fcntl.h>

int    open_file(token_t **tokens, int type)
{
    int fd;
	
	if (type == GREAT)
    	fd = open((*tokens)->next->data, O_RDWR | O_CREAT | O_TRUNC, 0777);
	else if (type == LESS)
    	fd = open((*tokens)->next->data, O_RDWR, 0777);
	else if (type == DGREAT)
    	fd = open((*tokens)->next->data, O_RDWR | O_CREAT | O_APPEND, 0777);
	else if (type == DLESS)
	{
		fd = heredoc(ft_strdup((*tokens)->next->data));
	}
	if (fd < 0)
	{
		if ((*tokens)->next->old_data == NULL)
			perror("the error");
		else
		{
			printf("minishell: %s: ambiguous redirect\n", (*tokens)->next->old_data);
			free((*tokens)->next->old_data);
		}
	}
	// close(fd);
	return (fd);
}

// void	check_file_direc_rm_token(token_t **tokens, t_cmd **cmds, int i)
// {
// 	if ((*tokens)->prev == NULL)
// 		(*cmds)->tokens_cmd = (*tokens)->next->next;
// 	rm_token(&(*tokens)->next);
// 	rm_token(tokens);
// 		// printf("--- %s\n", (*tokens)->next->data);
// }
void	rm_redirecitons(t_cmd **cmds, int pipes)
{
	int	i;
	token_t	*tmp;

	i = 0;
	while(i <= pipes)
	{
		while (((*cmds)[i].tokens_cmd) != NULL 
		&& ((((*cmds)[i].tokens_cmd))->type == LESS || ((*cmds)[i].tokens_cmd)->type == GREAT
		|| (((*cmds)[i].tokens_cmd))->type == DLESS || ((*cmds)[i].tokens_cmd)->type == DGREAT))
		{
			rm_token(&((*cmds)[i].tokens_cmd));
			rm_token(&((*cmds)[i].tokens_cmd));
		}
		tmp = ((*cmds)[i].tokens_cmd);
		while (tmp != NULL)
		{
			if ((tmp->next != NULL) && (tmp->next->type == LESS || tmp->next->type == GREAT
			|| tmp->next->type == DLESS || tmp->next->type == DGREAT))
			{
				rm_token(&(tmp->next));
				rm_token(&(tmp->next));
				continue;
			}
			tmp = tmp->next;
		}
		i++;
	}
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
				{
					if (close((*cmds)[i].infile) == -1)
					{
						perror("close : ");
						exit(3);
					}
				}
				if (fd == -1)
				{
					(*cmds)[i].exec = 0;
					gen.exit_status = 1;
					//this is in doubt
					return ;
				}
				(*cmds)[i].infile = fd;
			}
			else if (tokens->type == GREAT || tokens->type == DGREAT)
			{
                fd = open_file(&tokens, tokens->type);
				if ((*cmds)[i].outfile != -1)
				{
					if (close((*cmds)[i].outfile) == -1)
					{
						perror("close : ");
						exit(3);
					}
				}
				if (fd == -1)
				{
					(*cmds)[i].exec = 0;
					gen.exit_status = 1;
					return ;
				}
				(*cmds)[i].outfile = fd;
			}
			tokens = tokens->next;
        }
        i++;
    }
}