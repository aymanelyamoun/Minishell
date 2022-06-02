/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufisaou <oufisaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:28:41 by oufisaou          #+#    #+#             */
/*   Updated: 2022/06/02 18:26:46 by oufisaou         ###   ########.fr       */
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
    while(env)
    {
        printf("%s\n", env->content);
        env = env->next;
    }
    //handle_signals();
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
                continue;
            //heck_operators(tokens);
            //check_redirection(tokens);
            
            //return 1;
            //syntax_ana(tokens);
        }
		else
			exit(0); //last status
    }
    return (0);
}

t_list *env_create(char **envp)
{
    t_list *tmp = NULL;
    t_list *head;
    char *s;
    int index;


    index = 1;
    if(!(**envp) || !(envp) || !(envp[0]))
    {
        head = ft_lstnew(NULL);
        return (head);
    }
    s = ft_strdup(envp[0]);
    head = ft_lstnew(s);
    ft_lstadd_back(&head, tmp);
    while(envp[index])
    {
        s = ft_strdup(envp[index]);
        tmp = ft_lstnew(s);
        ft_lstadd_back(&head, tmp);
        index++;
    }
    return (head);
}