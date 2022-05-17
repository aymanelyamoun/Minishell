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

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    //handeling the enviroment variables
    //handelling the signals
    //handeling the location
    //prompting the user
    //add history
    //start tokenization
    //parsing execution
    (void)argc;
    (void)argv;
    (void)envp;
    char *inpt;
    int i = 0;

    while ( i < 5 )
    {
                inpt = readline(">>minishell ");
                add_history(inpt);
                printf("%s", inpt);
                printf("\n");
                ++i;
    }
    return 0;

}