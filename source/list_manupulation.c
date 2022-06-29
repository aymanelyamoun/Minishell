/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_manupulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufisaou <oufisaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 19:19:26 by ael-yamo          #+#    #+#             */
/*   Updated: 2022/06/29 20:07:24 by oufisaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


t_token *new_token(unsigned int type, char *data)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->type = type;
	token->data = data;
	token->old_data = NULL;
	token->next = NULL;
	token->prev = NULL;
	return token;
}

void	add_at_end(t_token **tokens_head, t_token *token)
{
	t_token	*tmp;

	tmp = *tokens_head;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	token->prev = tmp;
	tmp->next = token;
}

void	add_token_last(t_token **token_head, unsigned int type, char *data)
{
	if (*token_head == NULL)
		*token_head = new_token(type, data);
	else
		add_at_end(token_head, new_token(type, data));
}