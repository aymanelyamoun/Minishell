/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_manupulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-yamo <ael-yamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 19:19:26 by ael-yamo          #+#    #+#             */
/*   Updated: 2022/06/03 12:51:23 by ael-yamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


token_t *new_token(unsigned int type, char *data)
{
	token_t *token;

	token = malloc(sizeof(token_t));
	token->type = type;
	token->data = data;
	token->old_data = NULL;
	token->next = NULL;
	token->prev = NULL;
	return token;
}

void	add_at_end(token_t **tokens_head, token_t *token)
{
	token_t	*tmp;

	tmp = *tokens_head;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	token->prev = tmp;
	tmp->next = token;
}

void	add_token_last(token_t **token_head, unsigned int type, char *data)
{
	if (*token_head == NULL)
		*token_head = new_token(type, data);
	else
		add_at_end(token_head, new_token(type, data));
}