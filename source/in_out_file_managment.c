/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_file_managment.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-yamo <ael-yamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 01:52:14 by ael-yamo          #+#    #+#             */
/*   Updated: 2022/07/01 01:53:33 by ael-yamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	open_file_err(t_token **tokens, int fd, int status)
{
	if ((*tokens)->next->old_data == NULL && (fd == -1 && status != 1))
		perror("minishellllllll");
	else
	{
		if ((ft_strcmp((*tokens)->next->data, "") == 0) \
		&& (*tokens)->next->old_data != NULL)
			printf("minishell: %s: ambiguous redirect\n", \
			(*tokens)->next->old_data);
		else if ((*tokens)->next->old_data != NULL && status != 1)
			perror("minishelll");
	}
}

int	open_file(t_token **tokens, int type)
{
	int	fd;
	int	status;

	status = 0;
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
		open_file_err(tokens, fd, status);
	return (fd);
}

static void	rm_redi_utils(t_token **token1, t_token **token2)
{
	rm_token(token1);
	rm_token(token2);
}

static int	check_con_redi(t_cmd **cmds, int i)
{
	if (((*cmds)[i].tokens_cmd) != NULL 
		&& ((((*cmds)[i].tokens_cmd))->type == LESS 
		|| ((*cmds)[i].tokens_cmd)->type == GREAT
		|| (((*cmds)[i].tokens_cmd))->type == DLESS 
		|| ((*cmds)[i].tokens_cmd)->type == DGREAT))
		return (1);
	return (0);
}

void	rm_redirecitons(t_cmd **cmds, int pipes)
{
	int		i;
	t_token	*tmp;

	i = 0;
	while (i <= pipes)
	{
		while (check_con_redi(cmds, i))
			rm_redi_utils(&((*cmds)[i].tokens_cmd), &((*cmds)[i].tokens_cmd));
		tmp = ((*cmds)[i].tokens_cmd);
		while (tmp != NULL)
		{
			if ((tmp->next != NULL) && (tmp->next->type == LESS \
			|| tmp->next->type == GREAT \
			|| tmp->next->type == DLESS || tmp->next->type == DGREAT))
			{
				rm_redi_utils(&(tmp->next), &(tmp->next));
				continue ;
			}
			tmp = tmp->next;
		}
		i++;
	}
}

int	creat_in_files(t_cmd **cmds, t_token *tokens, int i)
{
	int	fd;

	fd = open_file(&tokens, tokens->type);
	if ((*cmds)[i].infile > -1)
	{
		if (close((*cmds)[i].infile) == -1)
			perror("close : ");
	}
	if (fd <= -1)
		(*cmds)[i].exec = fd * (-1);
	(*cmds)[i].infile = fd;
	return (fd);
}

int	creat_out_files(t_cmd **cmds, t_token *tokens, int i)
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

void	check_file_direcitons(t_cmd **cmds, int pipes)
{
	int		i;
	t_token	*tokens;
	int		fd;

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