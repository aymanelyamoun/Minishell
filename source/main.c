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
   // char **envir;
    char *line;
    (void)envp;
    (void)argv;
  
    if(argc != 1)
        return (1);
    // envir = set_env(envp);
    // handle_signals();
    while (1)
    {
        //line = readline("ENTER PROMPT   ");
        envi.read = "'d''vdfvdf";
        if(check_parant(line) == -1 || check_quotes(line) == -1) //add env for herdoc
        {
            printf("problem in begining\n");
            exit(1);
        }
        if (envi.read != NULL)
        {
            // token_t *t;
            // // int index;
            // t= NULL;
            //add_history(line);
            tokenize(envi.read);
            return (1);
            //syntax_ana(tokens);
        }
		else
			exit(0); //last status
    }
    return (0);
}

// void print(token_t *head) {
//     token_t *current_node = head;
//    	while ( current_node != NULL) {
//         printf("%s ", current_node->data);
//         current_node = current_node->next;
//     }
// }