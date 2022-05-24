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
    char **envir;
    char *input;

    if(argc != 1)
        return (1);
    envir = set_env(envp);
    handle_signals();
    while(1337)
    {
        input = readline("Minishell>"); //it should be updated to the 
    }
}
void    terminal_settings(void)
{
    int set;
    struct termios  term;

    set = tcgetattr(STDIN_FILENO, &term);
    term.c_cflag &= ~ECHOCTL;
    tcsetattr(STDIN_FILENO, set, &term);

}
void handle_signals(void)
{
    signal(SIGQUIT, handler);
    signal(SIGINT, handler);
    terminal_settings();
}

void    handler(int sig)
{
    if(sig == SIGINT)
    {
        rl_on_new_line();
        ft_putstr_fd("\n", 2);
        rl_replace_line("", 1);
        rl_redisplay();
    }
    else if (sig == SIGQUIT)
    {
        rl_on_new_line();
        rl_replace_line("", 1);
        rl_redisplay();
        return ;
    }
    return ;
}

char **set_env(char **envp)
{
    int index;
    char **tmp;

    if(envp)
    {
        index = 0;
        while(envp[index])
            index++;
    }
    tmp = malloc(sizeof(char *) * (index + 1));
    if (!tmp)
        return (NULL);
    index = 0;
    while(envp[index])
    {
        tmp[index] = ft_strdup(envp[index])
        index++;
    }
    tmp[index] = NULL;
    return (tmp);
}