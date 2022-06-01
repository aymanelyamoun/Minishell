/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufisaou <oufisaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:28:41 by oufisaou          #+#    #+#             */
/*   Updated: 2022/05/16 20:09:26 by oufisaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
    char **envir;
    char *line;
    token_t *tokens;
    if(argc != 1)
        return (1);
    envir = set_env(envp);
    handle_signals();
    while (1)
    {
        line = readline("ENTER PROMPT   ");
        if(check_parent(line) == -1 || check_quotes(line) == -1) //add env for herdoc
            //free **envir and exit
        if (line != NULL)
        {
            add_history(line);
            tokens = tokenize(line);
            syntax_ana(tokens);
        }
		else
			exit(0); //last status
    }
    return (0);
}

