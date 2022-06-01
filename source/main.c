/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufisaou <oufisaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:28:41 by oufisaou          #+#    #+#             */
/*   Updated: 2022/06/01 12:07:04 by oufisaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
    // char **envir;
    char *line;
    token_t *tokens;
    
    (void)envp;
    (void)argv;
    if(argc != 1)
        return (1);
    //envir = set_env(envp);
    //handle_signals();
    while (1)
    {
        line = readline("Minishell>>");
        if (line != NULL)
        {
            add_history(line);
            tokens = tokenize(line);
            check_quotes(tokens);
            //return 1;
            //syntax_ana(tokens);
        }
		else
			exit(0); //last status
    }
    return (0);
}

