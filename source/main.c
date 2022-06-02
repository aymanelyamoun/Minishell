/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufisaou <oufisaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:28:41 by oufisaou          #+#    #+#             */
/*   Updated: 2022/06/02 21:19:59 by oufisaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list *env;

int main(int argc, char **argv, char **envp)
{
    // char **envir;
    char *line;
    token_t *tokens;
    (void)envp;
    (void)argv;
    if(argc != 1)
        return (1);
    env = env_create(envp);
    // while(env)
    // {
    //     printf("%s\n", env->content);
    //     env = env->next;
    // }
    handle_signals();
    while (1)
    {
        line = readline("Minishell: ");
        if (line != NULL)
        {
            add_history(line);
            tokens = tokenize(line);
            if(check_quotes(tokens) == 1)
            {
                check_pipe(tokens);
                check_newline(tokens);
            }
            else
                continue ;
        }
		else
			exit(0); //last status
    }
    return (0);
}

