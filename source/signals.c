/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufisaou <oufisaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:51:38 by oufisaou          #+#    #+#             */
/*   Updated: 2022/06/02 21:24:22 by oufisaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void    terminal_settings(void)
// {
//     int set;
//     struct termios  term;

//     set = tcgetattr(STDIN_FILENO, &term);
//     term.c_cflag &= ~ECHOCTL;
//     tcsetattr(STDIN_FILENO, set, &term);

// }
// void handle_signals(void)
// {
//     //terminal_settings();
//     signal(SIGQUIT, handler);
//     signal(SIGINT, handler);
    
// }

// void    handler(int sig)
// {
//     //rl_catch_signals = 0;
//     if(sig == SIGINT)
//     {
//         ft_putstr_fd("\n", 2);
//         rl_replace_line("", 1);
//         rl_on_new_line();
//     }
//     return ;
// }
int    terminal_settings(void)
{
    // struct termios  term;

    // if (tcgetattr(STDIN_FILENO, &term) == -1)
    //     return (1);
    // term.c_lflag &= ~(ECHOCTL);
    // tcsetattr(STDIN_FILENO, TCSANOW, &term);
    // signal(SIGQUIT, handler);
    // signal(SIGINT, handler);
    rl_catch_signals = 0;
    return (0); 

}
int handle_signals(void)
{
    terminal_settings();
    return (0);
}

void    handler(int sig)
{
    if(sig == SIGINT)
    {
        ft_putstr_fd("\n", 2);
        rl_replace_line("", 1);
        rl_on_new_line();
    }
    rl_on_new_line();
    rl_redisplay();
}
// int ctrld(void)
// {
//     rl_on_new_line();
//     rl_redisplay();
//     //ft_putstr_fd("quit\n", 2);
//     return (1);
// }