/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufisaou <oufisaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 11:18:42 by oufisaou          #+#    #+#             */
/*   Updated: 2022/06/18 00:57:19 by oufisaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

token_t *error_free(char *str, token_t *tokens)
{
    ft_putstr_fd("bash: syntax error near unexpected token ", 2);
    ft_putstr_fd("\'", 2);
    ft_putstr_fd(str, 2);
	ft_putstr_fd("\'", 2);
	ft_putstr_fd("\n", 2);
	//free_all(tokens);
	return (NULL);
}


void	free_all(token_t *tokens)
{
	token_t	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->data);
		tmp->data = NULL;
		free(tmp);
		tmp = NULL;
	}
}