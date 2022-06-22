#include "../includes/minishell.h"
int    terminal_settings(void)
{
    struct termios  term;

    if (tcgetattr(0, &term) == -1)
        return (1);
    term.c_lflag &= ~(ECHOCTL);
    tcsetattr(0, TCSANOW, &term);
    signal(SIGQUIT, handler);
    signal(SIGINT, handler);
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

int ctrld(void)
{
    rl_on_new_line();
    rl_redisplay();
    ft_putstr_fd("exit\n", 2);
    exit(1);
}