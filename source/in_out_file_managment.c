#include "../includes/minishell.h"
#include <fcntl.h>

int    open_file(token_t **tokens, int type)
{
    int fd;
	int	status;
	
	if (type == GREAT)
    	fd = open((*tokens)->next->data, O_RDWR | O_CREAT | O_TRUNC, 0777);
	else if (type == LESS)
    	fd = open((*tokens)->next->data, O_RDWR, 0777);
	else if (type == DGREAT)
    	fd = open((*tokens)->next->data, O_RDWR | O_CREAT | O_APPEND, 0777);
	else if (type == DLESS)
	{
		if ((*tokens)->next->old_data)
			fd = heredoc(ft_strdup((*tokens)->next->old_data), &status);
		else
			fd = heredoc(ft_strdup((*tokens)->next->data), &status);

		if (status)
			fd = status * (-1);
	}
	if (fd < 0)
	{
		if ((*tokens)->next->old_data == NULL && fd == -1)
			perror("minishellllllll");
		else 
		{
			if ((ft_strcmp((*tokens)->next->data, "") == 0) && (*tokens)->next->old_data != NULL)
				printf("minishell: %s: ambiguous redirect\n", (*tokens)->next->old_data);
			else if ((*tokens)->next->old_data != NULL)
				perror("minishelll");
			free((*tokens)->next->old_data);
		}
	}
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

int		creat_in_files(t_cmd **cmds, token_t *tokens, int i)
{
	int	fd;

	fd = open_file(&tokens, tokens->type);
	if ((*cmds)[i].infile != -1)
	{
		if (close((*cmds)[i].infile) == -1)
		{
			perror("close : ");
			exit(3);
		}
	}
	if (fd <= -1)
		(*cmds)[i].exec = fd * (-1);
	(*cmds)[i].infile = fd;
	return (fd);
}

int		creat_out_files(t_cmd **cmds, token_t *tokens, int i)
{
	int	fd;

	fd = open_file(&tokens, tokens->type);
	if ((*cmds)[i].outfile != -1)
	{
		if (close((*cmds)[i].outfile) == -1)
		{
			perror("close : ");
			exit(3);
		}
	}
	if (fd <= -1)
		(*cmds)[i].exec = fd * (-1);
	(*cmds)[i].outfile = fd;
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
            if (tokens->type == LESS || tokens->type == DLESS)
				fd = creat_in_files(cmds, tokens, i);
			else if (tokens->type == GREAT || tokens->type == DGREAT)
				fd = creat_out_files(cmds, tokens, i);
			if (fd == -1)
				return ;
			tokens = tokens->next;
        }
        i++;
    }
}