// #include "../includes/minishell.h"

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
//     signal(SIGQUIT, handler);
//     signal(SIGINT, handler);
//     terminal_settings();
// }

// void    handler(int sig)
// {
//     if(sig == SIGINT)
//     {
//         rl_on_new_line();
//         ft_putstr_fd("\n", 2);
//         rl_replace_line("", 1);
//         rl_redisplay();
//     }
//     else if (sig == SIGQUIT)
//     {
//         rl_on_new_line();
//         rl_replace_line("", 1);
//         rl_redisplay();
//         return ;
//     }
//     return ;
// }