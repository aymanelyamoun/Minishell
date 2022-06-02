/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufisaou <oufisaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:51:38 by oufisaou          #+#    #+#             */
/*   Updated: 2022/06/02 15:38:58 by oufisaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//rl_replace_line not working.
// void    handler(int sig)
// {
//     rl_catch_signals = 0;
//     if(sig == SIGINT)
//     {
//         ft_putstr_fd("\n", 2);
//         rl_replace_line("", 1);
//         rl_on_new_line();
//     }
//     rl_on_new_line();
//     rl_redisplay();
// }

// int ctrld(void)
// {
//     rl_on_new_line();
//     rl_redisplay();
//     ft_putstr_fd("quit\n", 2);
//     return (1);
// }